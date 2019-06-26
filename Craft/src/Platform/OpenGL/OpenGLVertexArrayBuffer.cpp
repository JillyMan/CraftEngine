#include "crpch.h"

#include "Platform\OpenGL\OpenGL.h"
#include "OpenGLVertexArrayBuffer.h"

namespace Craft
{
	VertexArrayBuffer* VertexArrayBuffer::Create()
	{
		return new OpenGLVertexArrayBuffer();
	}

	Craft::OpenGLVertexArrayBuffer::OpenGLVertexArrayBuffer()
	{
		glCreateVertexArrays(1, &m_BufferId);
	}

	Craft::OpenGLVertexArrayBuffer::~OpenGLVertexArrayBuffer()
	{
		glDeleteVertexArrays(1, &m_BufferId);
	}

	void Craft::OpenGLVertexArrayBuffer::Bind()
	{
		glBindVertexArray(m_BufferId);
	}

	void Craft::OpenGLVertexArrayBuffer::Unbind()
	{
		glBindVertexArray(0);
	}

	void Craft::OpenGLVertexArrayBuffer::AddVertexBuffer(VertexBuffer* buffer)
	{
		Bind();
		buffer->Bind();
		Bind();
		//need parse buffer....
		//....

		m_VertexBuffers.push_back(buffer);
	}

	void Craft::OpenGLVertexArrayBuffer::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
	}
}