#pragma once

#include "Buffer.h"

namespace Craft {

	class VertexArray
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void AddVertexBuffer(VertexBuffer* buffer) = 0;
		virtual void SetIndexBuffer(IndexBuffer* buffer) = 0;

		virtual u32 GetCountIndices() = 0;

		static VertexArray* Create();
	};
}