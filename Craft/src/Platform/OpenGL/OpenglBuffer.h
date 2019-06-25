#pragma once

#include "OpenGL.h"
#include "Craft\Graphics\Buffer.h"

namespace Craft
{
	static GLenum GetOpenGLEnumType(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::Float:		return GL_FLOAT;
			case ShaderDataType::Float2:	return GL_FLOAT;
			case ShaderDataType::Float3:	return GL_FLOAT;
			case ShaderDataType::Float4:	return GL_FLOAT;
			case ShaderDataType::Int:		return GL_INT;
			case ShaderDataType::Int2:		return GL_INT;
			case ShaderDataType::Int3:		return GL_INT;
			case ShaderDataType::Int4:		return GL_INT;
			case ShaderDataType::Bool:		return GL_BOOL;
		}
		
		CR_ASSERT(false, "Invalid data type");
		return GL_NONE;
	}

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(f32* vertices, s32 size);
		~OpenGLVertexBuffer();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddBufferAttribute(BufferAttribute& attribute) override
		{
			m_Atribs.push_back(attribute);
		}

		virtual std::vector<BufferAttribute>& GetAttribs() override
		{
			return m_Atribs;
		}

		u32 GetCount() override { return m_Size; }

	private:
		std::vector<BufferAttribute> m_Atribs;
		GLint m_Size;
		GLuint m_BufferId;
		GLuint m_AttribCounter;
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