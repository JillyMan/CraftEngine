#pragma once

namespace Craft
{
	class VertexBuffer
	{
	public: 
		virtual ~VertexBuffer() { }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetCount() = 0;

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