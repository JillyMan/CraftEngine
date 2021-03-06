#pragma once

#ifdef CRAFT_PLATFORM_WINDOWS
extern Craft::Application* Craft::CreateApplication();

int main(int argv, char** args)
{
	Craft::Log::Init();
	CR_CORE_INFO("Log init.");

	Craft::Application* App = Craft::CreateApplication();
	App->Run();
	return 0;
}

#endif