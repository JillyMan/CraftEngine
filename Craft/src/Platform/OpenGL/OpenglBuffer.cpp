#include "crpch.h"
#include "OpenglBuffer.h"

namespace Craft
{
	VertexBuffer* VertexBuffer::Create(f32* vertices, s32 size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(f32* vertices, s32 size) : 
		m_AttribCounter(0), 
		m_Size(size)
	{
		glCreateBuffers(1, &m_BufferId);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size * sizeof(f32), vertices, GL_DYNAMIC_DRAW);
		Unbind();
	}

	OpenGLVertexBuffer::~OpenGLVertexBuffer()
	{
		glDeleteBuffers(GL_ARRAY_BUFFER, &m_BufferId);
	}

	void Craft::OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	}

	void Craft::OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
}
