#include <Craft.h>

#include "Craft/ImGui/ImGuiLayer.h"

#include "Layers/Sample2DLayer.h"
//#include "Layers/Sample3DLayer.h"

/*
	todo: Shader: make local cache for names location

*/

#define CRAFT_TEST

#ifndef CRAFT_TEST
void MathTest()
{
	Craft::v3 a{ 1,2,3 };
	Craft::v3 b{ 1,2,3 };
	Craft::v3 c = a + b;
	std::cout << "A:			" << a << std::endl;
	std::cout << "B:			" << b << std::endl;
	std::cout << "Dot a*b:		" << Dot(a, b)		<< std::endl;
	std::cout << "Cross a^b:	" << Cross(a, b)	<< std::endl;
	std::cout << "Scalar a+10:	" << (a + 10.0f)	<< std::endl;
	std::cout << "c = a + b:	" << (a + b)		<< std::endl;
	std::cout << "Length(c):	" << Length(c)		<< std::endl;
	std::cout << "Normalize(c):	" << Normalize(c)	<< std::endl;

	mat4 mat0 = mat4::Identity(1.0);
	mat4 mat1 = mat4::Identity(2.0);
	mat4 mat2 = mat0 + mat1;
	mat4 mat3 = mat0 * mat2;

	std::cout << "math: " << "\n" << mat2 << std::endl;
	std::cout << "m0*m1: " << "\n" << mat3 << std::endl;
}
#endif

void CommonTest() 
{
#ifndef CRAFT_TEST
	MathTest();
#endif
}

class Sandbox : public Craft::Application
{
public:
	Sandbox(Craft::WindowSetting setting) : Application(setting)
	{
		CommonTest();
		PushLayer(new Sample2DLayer());
		//PushLayer(new Sample3DLayer());
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
