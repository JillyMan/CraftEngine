#include <Craft.h>

//#include "Layers/Sample2DLayer.h"
//#include "Layers/Sample3DLayer.h"
#include "Layers/Scene3D.h"

/*
	TODO:
		- glGetShaderiv (.., GL_INFO_LOG_LENGTH, &...); - get len of shader compile status 
			- also try to add common mechanism for getting opengl status.

		- Automatic load avaliable opengl version. 
			(use glGetString(type) with params like GL_VERSION, GL_SHADING_LANGUAGE_VERSION)

		- Make precompiled shaders.


		- Thins about rewrite abstraction for buffers.
		- Make more safity binding of vertex attr's to shader in attr's.
		- Add to log info __FILE__ and Position info
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
