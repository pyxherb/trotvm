#ifndef _XYLO_AST_TYPENAME_H_
#define _XYLO_AST_TYPENAME_H_

#include "astnode.h"

namespace xylo {
	enum class TypeNameKind : uint8_t {
		Void = 0,
		I8,
		I16,
		I32,
		I64,
		U8,
		U16,
		U32,
		U64,
		F32,
		F64,
		String,
		Bool,
		Custom,

		Array,
		Pointer,
		Ref
	};

	class TypeNameNode : public AstNode {
	public:
		TypeNameKind typeNameKind;

		XYLO_API TypeNameNode(TypeNameKind typeNameKind, peff::Alloc *selfAllocator);
		XYLO_API ~TypeNameNode();
	};

	class VoidTypeNameNode : public TypeNameNode {
	public:
		XYLO_API VoidTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~VoidTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I8TypeNameNode : public TypeNameNode {
	public:
		XYLO_API I8TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~I8TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I16TypeNameNode : public TypeNameNode {
	public:
		XYLO_API I16TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~I16TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I32TypeNameNode : public TypeNameNode {
	public:
		XYLO_API I32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~I32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class I64TypeNameNode : public TypeNameNode {
	public:
		XYLO_API I64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~I64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U8TypeNameNode : public TypeNameNode {
	public:
		XYLO_API U8TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~U8TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U16TypeNameNode : public TypeNameNode {
	public:
		XYLO_API U16TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~U16TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U32TypeNameNode : public TypeNameNode {
	public:
		XYLO_API U32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~U32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class U64TypeNameNode : public TypeNameNode {
	public:
		XYLO_API U64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~U64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F32TypeNameNode : public TypeNameNode {
	public:
		XYLO_API F32TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~F32TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class F64TypeNameNode : public TypeNameNode {
	public:
		XYLO_API F64TypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~F64TypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class StringTypeNameNode : public TypeNameNode {
	public:
		XYLO_API StringTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~StringTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class BoolTypeNameNode : public TypeNameNode {
	public:
		XYLO_API BoolTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~BoolTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};

	class CustomTypeNameNode : public TypeNameNode {
	public:
		peff::DynArray<peff::String> path;
		peff::DynArray<peff::RcObjectPtr<TypeNameNode>> genericArgs;

		XYLO_API CustomTypeNameNode(peff::Alloc *selfAllocator);
		XYLO_API ~CustomTypeNameNode();

		XYLO_API virtual void onRefZero() noexcept override;
	};
}

#endif
