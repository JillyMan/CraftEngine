#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Graphics/Core/Buffer.h>
#include <Craft/Graphics/Core/Texture.h>
#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Tools/Camera/Camera.h>

#include "./SpriteBatchItem.h"

namespace Craft { namespace Graphics {

	class SpriteBatcher {
	private:
		std::vector<SpriteBatchItem> _batches;

	public:
		SpriteBatchItem* CreateSpriteBatchItem() {
			_batches.push_back(SpriteBatchItem());
			return &_batches[_batches.size() - 1];
		}
	};

	class SpriteBatch {
	private: 
		VertexBuffer* _vertexBuffer;

		struct SceneData
		{
			mat4 m_ViewMatrix;
			mat4 m_ProjectionMatrix;
		};
	public:

		void Begin(Camera* camera, Shader* shader);
		void Submit(Texture* texture, v2 pos, Rectangle size, v4 color = v4(1.0f));
		void End();
	};
} }