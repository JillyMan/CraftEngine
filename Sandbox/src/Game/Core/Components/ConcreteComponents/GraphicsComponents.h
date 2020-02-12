#pragma once

#include <Craft/Graphics/Primitives/NewApi/Rectangle.h>

#include "../TransformComponent.h"
#include "../Abstractions/GraphicsComponent.h"

class SpriteGraphicsComponent : public GraphicsComponent {
private:
	Craft::Graphics::Shader* m_Shader;
	Craft::Graphics::Rectangle m_Rect;
	Craft::v3 m_Color;

public:
	SpriteGraphicsComponent(Craft::v2 size, Craft::v3 color, Craft::Graphics::Shader* shader) :
		m_Shader(shader),
		m_Rect(size)
	{
	}

	virtual void Draw(GameObject& obj) override {
		//Transform2D& transform = obj.Transform;
		Craft::mat4& modelMatrix = transform.ToModelMatrix();
		/*
			Renderer.Begin(Camera, shader);
			Renderer.Push(sprite, transform);
			/........./
			Renderer.Push(sprite, transform);
			Renderer.End();
		*/
	}
};