#pragma once

#ifdef CRAFT_PLATFORM_WINDOWS
extern Craft::Application* Craft::CreateApplication();

int main(int argv, char** args)
{
	printf("Craft Engine");
	Craft::Application* App = Craft::CreateApplication();
	App->Run();
	return 0;
}

#endif