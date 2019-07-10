#include "crpch.h"
#include "Renderer.h"

namespace Craft
{
	Renderer::SceneData Renderer::Data;

	void Renderer::BeginScene(Camera& camera)
	{
		Data.m_ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::Submit(Shape& shape)
	{
		shape.BeginDraw();
		shape.SetViewProjectinMatrix(Data.m_ViewProjectionMatrix);

		RenderCommand::DrawIndexed(shape.vertexArray);
	}
}
