#pragma once

#include "Craft\Graphics\VertexArrayBuffer.h"

namespace Craft
{
	class OpenGLVertexArrayBuffer : public VertexArrayBuffer
	{
	public:
		OpenGLVertexArrayBuffer();
		virtual ~OpenGLVertexArrayBuffer();

		virtual void Bind();
		virtual void Unbind();

		virtual void AddVertexBuffer(VertexBuffer* buffer);
		virtual void SetIndexBuffer(IndexBuffer* buffer);

		virtual u32 GetCountIndices() override { return m_IndexBuffer->GetCount(); }

	private:
		GLuint m_BufferId;
		IndexBuffer* m_IndexBuffer;
		std::vector<VertexBuffer*> m_VertexBuffers;
	};
}