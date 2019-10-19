#include "crpch.h"
#include <Platform/OpenGL/OpenglBuffer.h>

namespace Craft { namespace Graphics {

	static GLenum GetOpenGLEnumType(VertexDataType type)
	{
		switch (type)
		{
		case VertexDataType::Float:			return GL_FLOAT;
		case VertexDataType::Double:		return GL_FLOAT;
		case VertexDataType::Int:			return GL_INT;
		case VertexDataType::UnsignedInt:	return GL_UNSIGNED_INT;
		case VertexDataType::Bool:			return GL_BOOL;
		}

		CR_ASSERT(false, "Invalid data type");
		return GL_NONE;
	}

	VertexBuffer* VertexBuffer::Create(f32* vertices, s32 size)
	{
		return new OpenGLVertexBuffer(vertices, size);
	}

	OpenGLVertexBuffer::OpenGLVertexBuffer(f32* vertices, s32 size) :
		m_Size(size), m_Layout()
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

	void OpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_BufferId);
	}

	void OpenGLVertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	//------------------------------
	//---------Index buffer---------
	//------------------------------

	IndexBuffer* IndexBuffer::Create(u32* indices, s32 count)
	{
		return new OpenGLIndexBuffer(indices, count);
	}

	OpenGLIndexBuffer::OpenGLIndexBuffer(u32* indices, u32 size) :
		m_Count(size)
	{
		glCreateBuffers(1, &m_BufferId);
		Bind();
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, size * sizeof(u32), indices, GL_DYNAMIC_DRAW);
	}

	OpenGLIndexBuffer::~OpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &m_BufferId);
	}

	void OpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferId);
	}

	void OpenGLIndexBuffer::Unbind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}}