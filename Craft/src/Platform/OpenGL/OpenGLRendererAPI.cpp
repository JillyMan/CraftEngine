#include "crpch.h"

#include <Platform/OpenGL/OpenGL.h>
#include <Platform/OpenGL/OpenGLRendererAPI.h>

namespace Craft { namespace Graphics {

	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRendererAPI::SetClearColor(const v4 & color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}

	void OpenGLRendererAPI::DrawIndexed(VertexArray* vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, 0);
	}

	void OpenGLRendererAPI::DrawArrays(VertexArray* vertexArray)
	{
		//glDrawArrays(GL_TRIANGLES, 0, vertexArray->GetCountVertices());
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
} }