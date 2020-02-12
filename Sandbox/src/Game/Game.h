#pragma once

#include <Craft/Core/Layer.h>
#include <Craft/Math/Math.h>
#include <Craft/Event/EventMap.h>

#include <Craft/Graphics/Tools/Camera/Controllers/OrthoCameraContorller.h>

#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Primitives/Map.h>

#include <Craft/System/Vfs/Vfs.h>
#include "Prefab/LightSource.h"
#include "Core/Components/TransformComponent.h"

#include "Core/World/World.h"

using namespace Craft;

class Game : public Craft::Layer {
private:
	v2 m_Dimension;
	mat4 view;
	mat4 model;
	mat4 projection;
	v4 lightPos;

	Graphics::Cube m_Cube;
	Graphics::Torus m_Torus;
	Graphics::Shader* m_Shader;

private:
	f32 RotateSpeed = 10.0f;
	CameraController* m_CameraController;

private:
	Graphics::Cube m_LightMesh;
	Transform m_LightTransform;
	LigthSource m_LightSource;
	Graphics::Shader* m_LightShader;

private:
	System::Vfs m_Vfs;

private:
	Graphics::Rectangle rectMesh;
	Graphics::Shader* rectShader;
	World world;

public:
	Game(Craft::v2 m_Dimension);
	~Game();

	void OnEvent(Craft::Event& event) override;
	void OnUpdate(f32 deltaTime) override;
	void OnRender() override;
	void OnDebugRender() override;

private:

	void SetLights();
	void SetMatrices(v2 dim);
	bool OnMouseMove(Craft::MouseMovedEvent& event);

	bool m_IsRotating = false;
	v2 m_StartRotatePos;

	bool OnResizeWindow(Craft::WindowResizeEvent& event);
	bool OnKeyoardButtonPressed(Craft::KeyPressedEvent& event);
	bool OnMouseButtonPressed(Craft::MouseButtonPressedEvent& event);
	bool OnMouseButtonReleased(Craft::MouseButtonReleasedEvent& event);
};