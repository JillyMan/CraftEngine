#pragma once

#include <Craft/Graphics/Core/VertexArray.h>

namespace Craft { namespace Graphics {

	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void AddVertexBuffer(VertexBuffer* buffer) override;
		virtual void SetIndexBuffer(IndexBuffer* buffer) override;

		virtual IndexBuffer* GetIndexBuffer() override { return m_IndexBuffer; }
		virtual std::vector<VertexBuffer*> GetVertexBuffers() override { return m_VertexBuffers; }

	private:
		GLuint m_BufferId;
		u32 m_VertexBufferIndex = 0;
		IndexBuffer* m_IndexBuffer;
		std::vector<VertexBuffer*> m_VertexBuffers;
	};

}}