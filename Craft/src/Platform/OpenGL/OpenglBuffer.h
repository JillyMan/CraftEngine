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
		s32 GetSize() override { return m_Size; }

	private:
		GLint m_Size;
		GLuint m_BufferId;
		GLuint m_AttribCounter;
	};
}