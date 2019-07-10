#include "crpch.h"

#include "OpenGL.h"
#include "OpenGLRendererAPI.h"

namespace Craft
{
	void Craft::OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Craft::OpenGLRendererAPI::SetClearColor(const v4 & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void Craft::OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetCountIndices(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRendererAPI::DrawArrays(VertexArray* vertexArray)
	{
		glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetCountVertices());
	}

	void OpenGLRendererAPI::ZTest(bool enabled)
	{
		if (enabled)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}
}
