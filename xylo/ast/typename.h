#ifndef _XYLO_AST_TYPENAME_H_
#define _XYLO_AST_TYPENAME_H_

#include "idref.h"

namespace xylo {
	class VoidTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API VoidTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API VoidTypeNameNode(const VoidTypeNameNode &rhs);
		XYLO_API ~VoidTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I8TypeNameNode : public TypeNameNode {
	protected:
		virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API I8TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API I8TypeNameNode(const I8TypeNameNode &rhs);
		XYLO_API ~I8TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I16TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API I16TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API I16TypeNameNode(const I16TypeNameNode &rhs);
		XYLO_API ~I16TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I32TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API I32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API I32TypeNameNode(const I32TypeNameNode &rhs);
		XYLO_API ~I32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I64TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API I64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API I64TypeNameNode(const I64TypeNameNode &rhs);
		XYLO_API ~I64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U8TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API U8TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API U8TypeNameNode(const U8TypeNameNode &rhs);
		XYLO_API ~U8TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U16TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API U16TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API U16TypeNameNode(const U16TypeNameNode &rhs);
		XYLO_API ~U16TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U32TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API U32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API U32TypeNameNode(const U32TypeNameNode &rhs);
		XYLO_API ~U32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U64TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API U64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API U64TypeNameNode(const U64TypeNameNode &rhs);
		XYLO_API ~U64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F32TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API F32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API F32TypeNameNode(const F32TypeNameNode &rhs);
		XYLO_API ~F32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F64TypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API F64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API F64TypeNameNode(const F64TypeNameNode &rhs);
		XYLO_API ~F64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class StringTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API StringTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API StringTypeNameNode(const StringTypeNameNode &rhs);
		XYLO_API ~StringTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BoolTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		XYLO_API BoolTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API BoolTypeNameNode(const BoolTypeNameNode &rhs);
		XYLO_API ~BoolTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CustomTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		IdRefPtr idRefPtr;

		XYLO_API CustomTypeNameNode(peff::Alloc *selfAllocator, IdRefPtr &&idRefPtr);
		XYLO_API CustomTypeNameNode(const CustomTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~CustomTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class ArrayTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> elementType;

		XYLO_API ArrayTypeNameNode(peff::Alloc *selfAllocator, TypeNameNode *elementType);
		XYLO_API ArrayTypeNameNode(const ArrayTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~ArrayTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class PointerTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> pointedType;

		XYLO_API PointerTypeNameNode(peff::Alloc *selfAllocator, TypeNameNode *pointedType);
		XYLO_API PointerTypeNameNode(const PointerTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~PointerTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class MovedRefTypeNameNode : public TypeNameNode {
	protected:
		XYLO_API virtual peff::RcObjectPtr<AstNode> doDuplicate(peff::Alloc *newAllocator) const override;

	public:
		peff::RcObjectPtr<TypeNameNode> referencedType;

		XYLO_API MovedRefTypeNameNode(peff::Alloc *selfAllocator, TypeNameNode *referencedType);
		XYLO_API MovedRefTypeNameNode(const MovedRefTypeNameNode &rhs, peff::Alloc *allocator, bool &succeededOut);
		XYLO_API ~MovedRefTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
