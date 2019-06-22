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

		// Need delete, just now i'am lazy write struct BufferAttrib!!
		void SetAttrib(GLint size, GLenum type, GLboolean normalized, GLint stride, GLvoid* pointer = NULL)
		{
			Bind();
			glVertexAttribPointer(m_AttribCounter, size, type, normalized, stride, pointer);
			glEnableVertexAttribArray(m_AttribCounter++);
			Unbind();
		}
		// ---
		u32 GetCount() override { return m_Size; }

	private:
		GLint m_Size;
		GLuint m_BufferId;
		GLuint m_AttribCounter;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(u32* indices, s32 size);
		virtual ~OpenGLIndexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual u32 GetCount() override { return m_Count; }
	private:
		GLuint m_BufferId;
		GLuint m_Count;
	};
}