#include "crpch.h"

#include <Craft/Graphics/Renderer.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Craft { namespace Graphics {

	Renderer::SceneData Renderer::Data;

	void Renderer::BeginScene(Camera & camera)
	{
		Data.m_ViewMatrix = camera.GetViewMatrix();
		Data.m_ProjectionMatrix = camera.GetProjectionMatrix();
	}

	void Renderer::Submit(TriangleMesh& shape)
	{
		//shape.SetViewMatrix(Data.m_ViewMatrix);
		//shape.SetProjectionMatrix(Data.m_ProjectionMatrix);

		//shape.Render();

		RenderCommand::DrawIndexed(shape.GetVertexArray());
	}

	void Renderer::Submit(VertexArray* vertexArray, Shader* shader, Craft::mat4& transform)
	{
		shader->SetUniformMatrix4fv("vw_matrix", Data.m_ViewMatrix);
		shader->SetUniformMatrix4fv("pr_matrix", Data.m_ProjectionMatrix);
		shader->SetUniformMatrix4fv("ml_matrix", transform);
		shader->Use();

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
} }