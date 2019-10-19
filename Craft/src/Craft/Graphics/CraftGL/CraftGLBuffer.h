#pragma once

#include "Craft\Graphics\Buffer.h"


namespace Craft
{
	using namespace Craft::Graphics;

	class CraftGLVertexBuffer : public VertexBuffer
	{
	public:
		CraftGLVertexBuffer(f32* vertices, u32 size);
		virtual ~CraftGLVertexBuffer();

		void Bind();
		void Unbind();

	private:
		u32 m_RendererID;
	};

	class CraftGLIndexBuffer : public IndexBuffer
	{
	public:
		CraftGLIndexBuffer(f32* indices, u32 count);
		virtual ~CraftGLIndexBuffer();

		void Bind();
		void Unbind();

	private:
		u32 m_Count;
		u32 m_RendererID;
	};


}