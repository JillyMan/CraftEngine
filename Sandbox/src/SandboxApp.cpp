#include <Craft.h>

//#include "Layers/Sample2DLayer.h"
//#include "Layers/Sample3DLayer.h"
#include "Craft/ImGui/ImGuiLayer.h"
#include "Layers/Scene3D.h"

/*
	todo: Shader: make local cache for names location
*/

class Sandbox : public Craft::Application
{
public:
	Sandbox(Craft::WindowSetting setting) : Application(setting)
	{
		//PushLayer(new Sample2DLayer());
		//PushLayer(new Sample3DLayer());
		PushLayer(new Scene3D(Craft::v2(setting.Width, setting.Height)));
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
