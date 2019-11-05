#pragma once

#include <Craft/Event/KeyEvent.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Event/ApplicationEvent.h>

#include <Craft/Core/Layer.h>
#include <Craft/Graphics/Primitives/Shape.h>

#include <Craft/Graphics/Cameras/OrthoCameraContorller.h>

#include <Craft/Physic/Physic.h>

#include "../Scripts/PlayerController.h"

using namespace Craft;

class Sample2DLayer : public Layer
{
private:
	OrthoCameraController m_Camera;

	Graphics::Shader* m_Shader;
	Graphics::VertexArray* m_VertexArray;

	v3 m_Color = { 0.8f, 0.5f, 0.3f };
	f32 m_ScaleRatio = 1.0f;
	f32 m_Speed = 5.0f;
	v2 m_Origin = { 0.5f, 0.5f };

	Physic::RigidBody2DComponent* m_Block;

	PlayerController* m_PlayerController;

public:
	Sample2DLayer();
	~Sample2DLayer();

	virtual void OnEvent(Craft::Event& e) override;
	virtual void OnUpdate(f32 deltaTime)  override;
	virtual void OnRender() override;
	virtual void OnDebugRender() override;

private:

	void GraphicsInit();
	void PlayerInit();

	void SystemsUpdate(f32 dt);

	bool OnKeyDown(Craft::KeyPressedEvent& event);
	bool OnResizeWindow(Craft::WindowResizeEvent& event);

	void UpdatePlayer(f32 dt);
};
