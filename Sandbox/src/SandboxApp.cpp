#include <Craft.h>

class Sandbox : public Craft::Application
{
private:
	String m_EngineTitle = "Craft engine";
	Craft::Window* m_GameWindow;

public:
	Sandbox()
	{
		m_GameWindow = new Craft::Window(m_EngineTitle, Craft::WindowSetting());
	}
	
	void Run() override
	{
		while (!m_GameWindow->IsClose())
		{
			m_GameWindow->Update();
		}
	}

	virtual ~Sandbox()
	{
		delete m_GameWindow;
	}
};

Craft::Application* Craft::CreateApplication()
{
	return new Sandbox();
}