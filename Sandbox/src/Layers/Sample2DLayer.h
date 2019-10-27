#pragma once

#include <Craft/Event/KeyEvent.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Event/ApplicationEvent.h>

#include <Craft/Core/Layer.h>
#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Primitives/Shape.h>

#include <Craft/Physic/Physic.h>

using namespace Craft;

class Sample2DLayer : public Craft::Layer
{
private:
	Camera* m_Camera;

	Graphics::Shader* m_Shader;
	Graphics::VertexArray* m_VertexArray;

	v3 m_Color = { 0.8f, 0.5f, 0.3f };
	f32 m_ScaleRatio = 1.0f;
	f32 m_Speed = 0.5f;
	v2 m_Origin = { 0.5f, 0.5f };

	Physic::RigidBody* m_Player;
	Physic::RigidBody* m_Block;

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

	bool OnKeyDown(Craft::KeyPressedEvent& event);
	bool OnResizeWindow(Craft::WindowResizeEvent& event);
	bool OnMouseWheelScroll(Craft::MouseScrollWheelEvent& event);

	void UpdatePlayer(f32 dt);
};
