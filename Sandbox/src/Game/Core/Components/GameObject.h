#pragma once

#include <Craft.h>

#include "TransformComponent.h"
#include "Abstractions/InputComponent.h"
#include "Abstractions/GraphicsComponent.h"
#include "Abstractions/AnimationComponent.h"

class GameObject {
public:

	Transform2D Transform;

	GameObject(
		InputComponent* inputComponent,
		GraphicsComponent* graphicsComponent,
		AnimationComponent* animationComponent
	) :
		m_InputComponent(inputComponent),
		m_GraphicsComponent(graphicsComponent),
		m_AnimationComponent(animationComponent) { }

	void Update(f32 dt) {
		m_InputComponent->Update(*this, dt);
		m_AnimationComponent->Animate(*this, dt);
		m_GraphicsComponent->Draw(*this);
	}

private:
	InputComponent*	m_InputComponent;
	GraphicsComponent* m_GraphicsComponent;
	AnimationComponent* m_AnimationComponent;
};