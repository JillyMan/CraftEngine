#pragma once

namespace Craft
{
	enum class ShaderDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	struct BufferAttribute
	{
		s32 Size;
		ShaderDataType DataType;
		bool Normalized;
		s32 Stride;
		void* Pointer;
	};

	class VertexBuffer
	{
	public: 
		virtual ~VertexBuffer() { }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetCount() = 0;

		virtual void AddBufferAttribute(BufferAttribute& attribute) = 0;
		virtual std::vector<BufferAttribute>& GetAttribs() = 0;

		static VertexBuffer* Create(f32* vertices, s32 size);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetCount() = 0;

		static IndexBuffer* Create(u32* indices, s32 count);
	};
}