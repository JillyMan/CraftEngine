#include <Craft.h>
#include "Platform\OpenGL\OpenGL.h"

class ExampleLayer : public Craft::Layer
{
public:
	ExampleLayer()
	{
	}

	virtual void OnEvent(Craft::Event& event) override
	{
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
	}

	virtual void OnRender() override
	{
		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);
	}
};

class Sandbox : public Craft::Application
{
public:
	Sandbox() : Application()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	return new Sandbox();
}