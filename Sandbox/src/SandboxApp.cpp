#include <Craft.h>

#include "Craft/ImGui/ImGuiLayer.h"
//#include "Layers/Sample2DLayer.h"
#include "Layers/Sample3DLayer.h"

/*
	todo: Shader: make local cache for names location
*/

class Sandbox : public Craft::Application
{
public:
	Sandbox(Craft::WindowSetting setting) : Application(setting)
	{
		//PushLayer(new Sample2DLayer());
		PushLayer(new Sample3DLayer());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	WindowSetting setting;
	setting.IsVSync = false;
	return new Sandbox(setting);
}
