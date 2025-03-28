#include "attribute.h"

using namespace xylo;

XYLO_API peff::RcObjectPtr<AstNode> AttributeDef::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<AttributeDef> duplicatedNode(peff::allocAndConstruct<AttributeDef>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API AttributeDef::AttributeDef(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Attribute, selfAllocator, mod),
	fields(selfAllocator),
	fieldIndices(selfAllocator) {
}

XYLO_API AttributeDef::AttributeDef(const AttributeDef &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut), fields(allocator), fieldIndices(allocator) {
	if(!succeededOut) {
		return;
	}

	if(!fields.resize(rhs.fields.size())) {
		succeededOut = false;
		return;
	}

	for(size_t i = 0 ; i < fields.size(); ++i) {
		peff::RcObjectPtr<VarNode> df;
		if(!(df = rhs.fields.at(i)->duplicate<VarNode>(allocator))) {
			succeededOut = false;
			return;
		}

		df->parent = this;

		fields.at(i) = df;

		if(!(fieldIndices.insert(df->name, std::move(df)))) {
			succeededOut = false;
			return;
		}
	}

	succeededOut = true;
}

XYLO_API AttributeDef::~AttributeDef() {
}

XYLO_API void AttributeDef::onRefZero() noexcept {
	peff::destroyAndRelease<AttributeDef>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}

XYLO_API peff::RcObjectPtr<AstNode> AttributeNode::doDuplicate(peff::Alloc *newAllocator) const {
	bool succeeded = false;
	peff::RcObjectPtr<AttributeNode> duplicatedNode(peff::allocAndConstruct<AttributeNode>(newAllocator, ASTNODE_ALIGNMENT, *this, newAllocator, succeeded));
	if ((!duplicatedNode) || (!succeeded)) {
		return {};
	}

	return duplicatedNode.get();
}

XYLO_API AttributeNode::AttributeNode(
	peff::Alloc *selfAllocator,
	Module *mod)
	: MemberNode(AstNodeType::Attribute, selfAllocator, mod),
	fieldData(selfAllocator) {
}

XYLO_API AttributeNode::AttributeNode(const AttributeNode &rhs, peff::Alloc *allocator, bool &succeededOut) : MemberNode(rhs, allocator, succeededOut), fieldData(allocator) {
	if(!succeededOut) {
		return;
	}

	if(!fieldData.resize(rhs.fieldData.size())) {
		succeededOut = false;
		return;
	}

	for(size_t i = 0 ; i < rhs.fieldData.size(); ++i) {
		peff::RcObjectPtr<ExprNode> dd;
		if(!(dd = rhs.fieldData.at(i)->duplicate<ExprNode>(allocator))) {
			succeededOut = false;
			return;
		}

		fieldData.at(i) = dd;
	}

	succeededOut = true;
}

XYLO_API AttributeNode::~AttributeNode() {
}

XYLO_API void AttributeNode::onRefZero() noexcept {
	peff::destroyAndRelease<AttributeNode>(selfAllocator.get(), this, ASTNODE_ALIGNMENT);
}
