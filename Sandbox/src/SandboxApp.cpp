#include <Craft.h>

//#include "Layers/Sample2DLayer.h"
//#include "Layers/Sample3DLayer.h"
#include "Game/Game.h"

/*
	TODO:
		- .....ADD CODE PROFILER.....
		- FIX CAMERA BAG (NEED MOVE FOR SHOW RENDER)
		- Use instansing for tile rendering
		- Make absulute path for - #include "" (in Game folder check this).
		- Make more FLEXIBLE mechanism binding of vertex attr.
		- Make precompiled shaders.
		- Think about rewrite abstraction for buffers.
		- Add to log info __FILE__ and Position info, FIX LOG SIZE BUFFER.
*/

class Sandbox : public Craft::Application
{
public:
	Sandbox(Craft::WindowSetting setting) : Application(setting)
	{
		//PushLayer(new Sample2DLayer());
		//PushLayer(new Sample3DLayer());
		PushLayer(new Game(Craft::v2(setting.Width, setting.Height)));
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
