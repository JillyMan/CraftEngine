#include <Craft.h>

class Sandbox : public Craft::Application
{
public:
	Sandbox() : Application()
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