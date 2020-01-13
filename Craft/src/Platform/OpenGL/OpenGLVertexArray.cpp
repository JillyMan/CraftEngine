#include "crpch.h"

#include "OpenGL.h"
#include "OpenGLVertexArray.h"

namespace Craft { namespace Graphics {

	static GLenum FromVertexDataTypeToOpenGLType(VertexDataType type)
	{
		switch (type)
		{
		case VertexDataType::Float:
		case VertexDataType::Float2:
		case VertexDataType::Float3:
		case VertexDataType::Float4:		return GL_FLOAT;

		case VertexDataType::Int:
		case VertexDataType::Int2:
		case VertexDataType::Int3:
		case VertexDataType::Int4:			return GL_INT;

		case VertexDataType::Mat3:			return GL_FLOAT;
		case VertexDataType::Mat4:			return GL_FLOAT;

		case VertexDataType::Bool:			return GL_BOOL;
		case VertexDataType::Double:		return GL_DOUBLE;
		case VertexDataType::UnsignedInt:	return GL_UNSIGNED_INT;
		}

		CR_ASSERT(false, "Invalid vertex data type!");
		return GL_NONE;
	}

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

	OpenGLVertexArray::OpenGLVertexArray() :
		m_BufferId(0),
		m_VertexBuffers(),
		m_VertexBufferIndex(0),
		m_IndexBuffer(nullptr)
	{
		glCreateVertexArrays(1, &m_BufferId);
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		for (auto& buf : m_VertexBuffers) 
		{
			delete buf;
		}
	
		delete m_IndexBuffer;
		glDeleteVertexArrays(1, &m_BufferId);
	}

	void OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_BufferId);
	}

	void OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	//todo: may be save only ptr on buffer, not for vector<verBuf*>
	void OpenGLVertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		CR_ASSERT(buffer, "Buffer not initilized!");
		Bind();
		buffer->Bind();

		const BufferLayout& layout = buffer->GetLayout();
		u32 bufferSize = buffer->GetCount();
		u32 stride = layout.GetStride();

		for (auto& element : layout)
		{
			glVertexAttribPointer(
				m_VertexBufferIndex,
				element.GetComponentCount(),
				FromVertexDataTypeToOpenGLType(element.DataType),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(GLvoid*)element.Offset
			);

			glEnableVertexAttribArray(m_VertexBufferIndex++);
		}

		m_VertexBuffers.push_back(buffer);
	}

	void OpenGLVertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
	}
} }