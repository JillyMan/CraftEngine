#pragma once

#include "OpenGL.h"
#include "Craft\Graphics\Buffer.h"

namespace Craft
{
	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(f32* vertices, s32 size);
		~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetLayout(BufferLayout& layout) { m_Layout = layout; }
		virtual const BufferLayout& GetLayout() override { return m_Layout; }

		u32 GetCount() override { return m_Size; }

	private:
		GLint m_Size;
		GLuint m_BufferId;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32* indices, u32 size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetCount() override { return m_Count; }
	private:
		GLuint m_BufferId;
		GLuint m_Count;
	};
}