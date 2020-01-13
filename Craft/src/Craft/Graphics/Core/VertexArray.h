#pragma once

#include "Buffer.h"

namespace Craft { namespace Graphics {

	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual IndexBuffer* GetIndexBuffer() = 0;
		virtual std::vector<VertexBuffer*> GetVertexBuffers() = 0;

		static VertexArray* Create();
	};
} }