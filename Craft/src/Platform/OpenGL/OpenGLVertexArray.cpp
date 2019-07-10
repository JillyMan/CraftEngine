#include "crpch.h"

#include "Platform\OpenGL\OpenGL.h"
#include "OpenGLVertexArray.h"

namespace Craft
{
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
	}

	VertexArray* VertexArray::Create()
	{
		return new OpenGLVertexArray();
	}

	Craft::OpenGLVertexArray::OpenGLVertexArray() : 
		m_VertexCount(0)
	{
		glCreateVertexArrays(1, &m_BufferId);
	}

	Craft::OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_BufferId);
	}

	void Craft::OpenGLVertexArray::Bind()
	{
		glBindVertexArray(m_BufferId);
	}

	void Craft::OpenGLVertexArray::Unbind()
	{
		glBindVertexArray(0);
	}

	void Craft::OpenGLVertexArray::AddVertexBuffer(VertexBuffer* buffer)
	{
		CR_ASSERT(buffer, "Buffer not initilized!");
		Bind();
		buffer->Bind();

		const BufferLayout&  layout = buffer->GetLayout();
		u32 bufferSize = buffer->GetCount();
		u32 stride = layout.GetStride();
		u32 index = 0;

		for (auto& element : layout)
		{
			glVertexAttribPointer(
				index,
				element.GetComponentCount(),
				FromVertexDataTypeToOpenGLType(element.DataType),
				element.Normalized ? GL_TRUE : GL_FALSE,
				stride,
				(GLvoid*)element.Offset
			);

			glEnableVertexAttribArray(index++);
		}

		m_VertexBuffers.push_back(buffer);
		m_VertexCount += buffer->GetCount();
	}

	void Craft::OpenGLVertexArray::SetIndexBuffer(IndexBuffer* buffer)
	{
		Bind();
		buffer->Bind();
		m_IndexBuffer = buffer;
	}
}