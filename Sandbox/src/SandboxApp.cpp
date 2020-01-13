#include <Craft.h>

//#include "Layers/Sample2DLayer.h"
//#include "Layers/Sample3DLayer.h"
#include "Craft/ImGui/ImGuiLayer.h"
#include "Layers/Scene3D.h"

/*
	TODO:
		- Shader: make local cache for names location
		- automatic load avaliable opengl version. 
			(use glGetString(type) with params like GL_VERSION, GL_SHADING_LANGUAGE_VERSION)
		- make precompiled shaders.
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
