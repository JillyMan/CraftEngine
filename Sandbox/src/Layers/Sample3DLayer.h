#pragma once

#include <Craft.h>
#include <Craft\Core\InputHandler.h>
#include <Craft\Graphics\Renderer.h>
#include <Craft\Graphics\RendererAPI.h>
#include <Craft\Graphics\RenderCommand.h>

#include <Craft\Graphics\Cameras\Camera.h>
#include <Craft\Graphics\Cameras\FPSCameraController.h>

#include <Craft\Graphics\Core\Texture.h>
#include <Craft\Graphics\Image\ImageLoader.h>

#include <Craft\Graphics\Primitives\Cube.h>
#include <Craft\Graphics\Primitives\Sprite.h>

//------ PLATFORM CODE -------
#include <Platform\OpenGL\OpenGL.h>
#include <Platform\OpenGL\OpenGLShader.h>
#include <Platform\OpenGL\OpenGLBuffer.h>
#include <Platform\OpenGL\OpenGLTexture.h>
#include <Platform\OpenGL\OpenGLVertexArray.h>
#include <Platform\OpenGL\OpenGLRendererAPI.h>
//----------------------------

#include "Constants.h"

using namespace Craft;
using namespace Graphics;
using namespace Vfs;

class Sample3DLayer : public Craft::Layer
{
private:

	std::vector<Shape*> m_Shapes;

	FPSCameraController* m_Camera;

	f32 timer = 0.0f;
	RotationKind rotKind;
	std::map<RotationKind, v3> rotors;

	Craft::Vfs::Vfs* m_Vfs;

public:
	Sample3DLayer()
	{
		m_Vfs = new Craft::Vfs::Vfs(RootSpritesFolder);
		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		InitRenderable();
	}

	~Sample3DLayer()
	{
		for (int i = 0; i < m_Shapes.size(); ++i)
		{
			delete m_Shapes[i];
		}
	}

	void InitRenderable()
	{
		rotKind = RotationKind::X;
		rotors[RotationKind::X] = v3(1.0f, 0.0f, 0.0f);
		rotors[RotationKind::Y] = v3(0.0f, 1.0f, 0.0f);
		rotors[RotationKind::Z] = v3(0.0f, 0.0f, 1.0f);

		RenderCommand::ZTest(true);
		RenderCommand::SetClearColor(v4(0.0f, 0.1f, 0.1f, 1.0f));

		v3 cameraPos = v3(0.0f, 0.0f, -5.0f);
		v3 cameraFront = v3(0.0f, 0.0f, -1.0f);
		v3 cameraUp = v3(0.0f, 1.0f, 0.0f);

		v2 lasMousePos = v2(DEFAULT_WINDOW_WIDTH / 2, DEFAULT_WINDOW_HEIGHT / 2);
		//m_Camera = new FPSCameraController(5.0f,
		//	cameraPos, cameraFront, cameraUp, lasMousePos,
		//	mat4::Perspective(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE));

		Craft::Image* smile = m_Vfs->GetImage(PathToSmileImage);
		Craft::Image* image = m_Vfs->GetImage(PathToTileSheets);
		Craft::Image* grass = m_Vfs->GetImage(PathToGrassImage);

		Sprite* m_Plane = new Sprite(10.0f, -4.0f, 10.0f, 10.0f, *grass);
		m_Plane->SetRotation(-90.0f, v3(1.0f, 0.0f, 0.0f));

		Sprite* m_Rect = new Sprite(0.0f, 0.0f, 1.0f, 1.0f, *smile);
		m_Rect->SetRotation(45.0f, v3(0.0f, 1.0f, 0.0f));

		Cube* m_Cube = new Cube(v3(0.0f, 2.0f, 0.0f), *image);
		m_Cube->SetRotation(55.0f, v3(0.0f, 0.0f, 1.0f));

		Cube* m_Cube1 = new Cube(v3(1.0f, -1.0f, 0.0f), *smile);
		m_Cube1->SetRotation(24.0f, v3(0.0f, 0.0f, 1.0f));

		Cube* m_Cube2 = new Cube(v3(3.0f, 1.0f, 0.0f), *smile);

		m_Shapes = {
			m_Plane,
			m_Rect,
			m_Cube,
			m_Cube1,
			m_Cube2
		};

		delete smile;
		delete grass;
		delete image;
	}

	void OnAttach()
	{
	}

	void OnDetach()
	{
	}

	virtual void OnRender() override
	{
		RenderCommand::Clear();
		Renderer::BeginScene(*m_Camera);

		for (Shape* shape : m_Shapes) {
			Renderer::Submit(*shape);
		}
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(Sample3DLayer::OnMouseMove));
		dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Sample3DLayer::OnResizeWindow));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Sample3DLayer::OnKeyDown));
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
		UpdateSettings();
		UpdateCamera(deltaTime);
		UpdateShapes(deltaTime);
	}

	void UpdateSettings()
	{
		if (Input::InputHandler::IsKeyPressed('1'))
		{
			rotKind = RotationKind::X;
		}
		else if (Input::InputHandler::IsKeyPressed('2'))
		{
			rotKind = RotationKind::Y;
		}
		else if (Input::InputHandler::IsKeyPressed('3'))
		{
			rotKind = RotationKind::Z;
		}
	}

	void UpdateShapes(f32 deltaTime)
	{
		timer += deltaTime;
		m_Shapes[2]->SetRotation(timer / 20.0f, v3(1.0f, 0.0f, 0.0f));
	}

	void UpdateCamera(f32 deltaTime)
	{
		UpdateCameraMove(deltaTime);
		UpdateCameraRotation(deltaTime, m_Camera->GetRotation(), rotors[rotKind]);
	}

	void UpdateCameraMove(f32 dt)
	{
		if (Input::InputHandler::IsKeyPressed('W'))
		{
			m_Camera->Move(MoveDirection::Up, dt);
		}
		if (Input::InputHandler::IsKeyPressed('S'))
		{
			m_Camera->Move(MoveDirection::Down, dt);
		}

		if (Input::InputHandler::IsKeyPressed('A'))
		{
			m_Camera->Move(MoveDirection::Left, dt);
		}
		if (Input::InputHandler::IsKeyPressed('D'))
		{
			m_Camera->Move(MoveDirection::Right, dt);
		}
	}

	void UpdateCameraRotation(f32 dt, f32 angle, v3& axis)
	{
		if (Input::InputHandler::IsKeyPressed('Q'))
		{
			m_Camera->SetRotation(angle + 1, axis);
		}
		if (Input::InputHandler::IsKeyPressed('E'))
		{
			m_Camera->SetRotation(angle - 1, axis);
		}
	}

private:
	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VK_ESCAPE)
		{
			exit(1);
		}

		return false;
	}

	bool OnMouseMove(Craft::MouseMovedEvent& e)
	{
		m_Camera->MouseMove(e.x, e.y);
		return true;
	}

	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}
};