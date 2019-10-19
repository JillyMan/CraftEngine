#pragma once

#include "Craft\Graphics\VertexArray.h"

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

		virtual u32 GetCountIndices() override { return m_IndexBuffer->GetCount(); }
		virtual u32 GetCountVertices() override { return m_VertexCount; }

	private:
		u32 m_VertexCount;
		GLuint m_BufferId;
		IndexBuffer* m_IndexBuffer;
		std::vector<VertexBuffer*> m_VertexBuffers;
	};

}}