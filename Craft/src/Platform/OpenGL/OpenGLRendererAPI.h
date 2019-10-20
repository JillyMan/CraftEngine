#pragma once

#include <Craft\Graphics\RendererAPI.h>

namespace Craft { namespace Graphics {
	
	class OpenGLRendererAPI : public RendererAPI
	{
	public:
		virtual void Clear() override;
		virtual void SetClearColor(const v4& color) override;

		virtual void DrawIndexed(VertexArray* vertexArray) override;
		virtual void DrawArrays(VertexArray* vertexArray) override;

		virtual void ZTest(bool enabled) override;
	};

}}