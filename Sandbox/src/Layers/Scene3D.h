#pragma once

#include <Craft/Math/Math.h>
#include <Craft/Core/Layer.h>
#include <Craft/Event/EventMap.h>

#include <Craft/Graphics/Core/Shader.h>
#include <Craft/Graphics/Primitives/NewApi/Cube.h>
#include <Craft/Graphics/Primitives/NewApi/Rectangle.h>
#include <Craft/Graphics/Cameras/FPSCameraController.h>

class Scene3D : public Craft::Layer {
private:
	Craft::v2 m_Dimension;
	Craft::FPSCameraController* m_Camera;

	Craft::v3 m_CubePos = Craft::v3();
	Craft::Graphics::TriangleMesh* m_Cube;
	Craft::Graphics::Rectangle* m_Rect;
	Craft::Graphics::Shader* m_Shader;

public:
	Scene3D(Craft::v2 m_Dimension);
	~Scene3D();

	void OnEvent(Craft::Event& event) override;
	void OnUpdate(f32 deltaTime) override;
	void OnRender() override;
	void OnDebugRender() override;

private:
	bool OnResizeWindow(Craft::WindowResizeEvent& event);

};