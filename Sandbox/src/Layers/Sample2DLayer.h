#pragma once

#include <Craft/Event/KeyEvent.h>
#include <Craft/Event/MouseEvent.h>
#include <Craft/Event/ApplicationEvent.h>

#include <Craft/Layer.h>
#include <Craft/Graphics/Cameras/Camera.h>
#include <Craft/Graphics/Primitives/Shape.h>

class Sample2DLayer : public Craft::Layer
{
private:
	Craft::Camera* m_Camera;

	Craft::Graphics::Shader* m_Shader;
	Craft::Graphics::VertexArray* m_VertexArray;
	Craft::v3 m_Color = { 0.8f, 0.5f, 0.3f };

	s32 xLast = 0, yLast = 0;

	Craft::v3 m_PlayerPos;
	Craft::mat4 m_PlayerTransform;

public:
	Sample2DLayer();
	~Sample2DLayer();

	virtual void OnEvent(Craft::Event& e) override;
	virtual void OnUpdate(f32 deltaTime)  override;
	virtual void OnRender() override;

	virtual void OnAttach() override;
	virtual void OnDetach() override;

private:
	bool OnKeyDown(Craft::KeyPressedEvent& event);
	bool OnResizeWindow(Craft::WindowResizeEvent& event);
	bool OnMouseWheelScroll(Craft::MouseScrollWheelEvent& event);

	void UpdatePlayer(f32 dt);

};
