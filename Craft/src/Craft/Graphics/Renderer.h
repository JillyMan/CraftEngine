#pragma once

#include <Craft/Graphics/RenderCommand.h>
#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Primitives/Shape.h>

#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Core/VertexArray.h>

#include <Craft/Math/Matrix.h>

namespace Craft { namespace Graphics {

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void Submit(Shape& shape);
		static void Submit(VertexArray* vertexArray, Shader* shader, Craft::mat4& transform);

	private:
		struct SceneData
		{
			mat4 m_ViewMatrix;
			mat4 m_ProjectionMatrix;
		};

		static SceneData Data;
	};
}}