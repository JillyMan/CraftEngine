#include <Craft.h>

class Sandbox : public Craft::Application
{
public:
	Sandbox()
	{
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	return new Sandbox();
}