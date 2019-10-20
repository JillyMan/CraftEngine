#pragma once

#include "Craft\Math\Vectors.h"
#include "VertexArray.h"

namespace Craft { namespace Graphics {
	class RendererAPI
	{
	public:
		enum class API
		{
			NONE = 0,
			OpenGL = 1
		};

		virtual void SetClearColor(const v4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(VertexArray* vertexArray) = 0;
		virtual void DrawArrays(VertexArray* vertexArray) = 0;

		virtual void ZTest(bool enabled) = 0;

		inline static API GetAPI() { return s_API; }

	private:
		static API s_API;
	};
} }