#include "Application.h"

#include "Log.h"
#include "Event\ApplicationEvent.h"

namespace Craft
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1024, 768);
		CR_TRACE(e);

		while (true)
		{
		}
	}

}
