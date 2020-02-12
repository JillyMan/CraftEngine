#pragma once

#include <Craft/Graphics/Core/Buffer.h>
#include <Craft/Graphics/Core/Texture.h>
#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Tools/Camera/Camera.h>

namespace Craft { namespace Graphics {

	class SpriteBatch {
	private: 

		struct SceneData
		{
			mat4 m_ViewMatrix;
			mat4 m_ProjectionMatrix;
		};

		VertexBuffer* _vertexBuffer;

		void Begin(Camera* camera, Shader* shader);

		void Submit(Texture* texture, );

		void End();

	};

} }