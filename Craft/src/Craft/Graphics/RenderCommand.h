#pragma once

#include "RendererAPI.h"

namespace Craft 
{
	class RenderCommand
	{
	public:
		inline static void SetClearColor(const v4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(VertexArray* vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}