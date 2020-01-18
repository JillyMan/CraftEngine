#pragma once

#include <Craft/Core/Layer.h>
#include <Craft/Math/Math.h>
#include <Craft/Event/EventMap.h>

#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Primitives/NewApi/Map.h>

#include <Craft/System/Vfs/Vfs.h>

using namespace Craft;

class Scene3D : public Craft::Layer {
private:
	v2 m_Dimension;
	mat4 view;
	mat4 model;
	mat4 projection;
	v4 lightPos;

	Graphics::Torus m_Torus;
	Graphics::Cube m_Cube;
	Graphics::Rectangle* m_Rect;
	Graphics::Shader* m_Shader;

private:
	v2 dv;
	f32 AmbientStrength = 1.0f;

private:
	System::Vfs m_Vfs;

public:
	Scene3D(Craft::v2 m_Dimension);
	~Scene3D();

	void OnEvent(Craft::Event& event) override;
	void OnUpdate(f32 deltaTime) override;
	void OnRender() override;
	void OnDebugRender() override;

private:

	void SetMatrices(v2 dim);
	bool OnMouseMove(Craft::MouseMovedEvent& event);

	bool m_IsRotating = false;
	v2 m_StartRotatePos;
	bool OnMouseButtonPressed(Craft::MouseButtonPressedEvent& event);
	bool OnMouseButtonReleased(Craft::MouseButtonReleasedEvent& event);

	bool OnResizeWindow(Craft::WindowResizeEvent& event);
};