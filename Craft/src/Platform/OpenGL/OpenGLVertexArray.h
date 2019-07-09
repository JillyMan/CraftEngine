#pragma once

#include "Craft\Graphics\VertexArray.h"

namespace Craft
{
	class OpenGLVertexArray : public VertexArray
	{
	public:
		OpenGLVertexArray();
		virtual ~OpenGLVertexArray();

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