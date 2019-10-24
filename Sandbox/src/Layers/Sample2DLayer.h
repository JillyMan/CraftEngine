#pragma once

#include <Craft/Event/KeyEvent.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Event/ApplicationEvent.h>

#include <Craft/Core/Layer.h>
#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Primitives/Shape.h>

struct RigidBody
{
	Craft::v3 P;
	Craft::v3 V;
	Craft::v3 A;
};

class Sample2DLayer : public Craft::Layer
{
private:
	Craft::Camera* m_Camera;

	Craft::Graphics::Shader* m_Shader;
	Craft::Graphics::VertexArray* m_VertexArray;
	Craft::v3 m_Color = { 0.8f, 0.5f, 0.3f };

	Craft::v3 m_PlayerPos;
	Craft::mat4 m_PlayerTransform;

	f32 m_ScaleRatio = 0.8f;
	f32 m_Speed = 1.0f;

	RigidBody m_Player;

public:
	Sample2DLayer();
	~Sample2DLayer();

	virtual void OnEvent(Craft::Event& e) override;
	virtual void OnUpdate(f32 deltaTime)  override;
	virtual void OnRender() override;
	virtual void OnDebugRender() override;

private:
	bool OnKeyDown(Craft::KeyPressedEvent& event);
	bool OnResizeWindow(Craft::WindowResizeEvent& event);
	bool OnMouseWheelScroll(Craft::MouseScrollWheelEvent& event);

	void UpdatePlayer(f32 dt);
};
