#pragma once

#include <Craft/Graphics/RenderCommand.h>
#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Primitives/Shape.h>

namespace Craft { namespace Graphics {

	class Renderer
	{
	public:
		static void BeginScene(Camera& camera);
		static void Submit(Shape& shape);

	private:
		struct SceneData
		{
			mat4 m_ViewMatrix;
			mat4 m_ProjectionMatrix;
		};

		static SceneData Data;
	};
}}