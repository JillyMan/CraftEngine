#include "crpch.h"

#include <Craft/Graphics/Renderer.h>

namespace Craft { namespace Graphics {

	Renderer::SceneData Renderer::Data;

	void Renderer::BeginScene(Camera & camera)
	{
		Data.m_ViewMatrix = camera.GetViewMatrix();
		Data.m_ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::Submit(Shape& shape)
	{
		shape.BeginDraw();

		shape.SetViewMatrix(Data.m_ViewMatrix);
		shape.SetProjectionMatrix(Data.m_ProjectionMatrix);

		RenderCommand::DrawIndexed(shape.GetVertexArray());
	}
} }