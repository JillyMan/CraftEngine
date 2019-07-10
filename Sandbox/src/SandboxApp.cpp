#include <map>
#include <Craft.h>

#include "Craft\Graphics\Renderer.h"
#include "Craft\Graphics\RendererAPI.h"
#include "Craft\Graphics\RenderCommand.h"

#include "Craft\Graphics\Camera.h"

#include "Craft\Graphics\Texture.h"
#include "Craft\Graphics\Image\ImageLoader.h"

//------ PLATFORM CODE -------
#include "Platform\OpenGL\OpenGL.h"
#include "Platform\OpenGL\OpenGLShader.h"
#include "Platform\OpenGL\OpenGLBuffer.h"
#include "Platform\OpenGL\OpenGLTexture.h"
#include "Platform\OpenGL\OpenGLVertexArray.h"
#include "Platform\OpenGL\OpenGLRendererAPI.h"
//----------------------------

using namespace Craft;

#define S_BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)
#define ArrayCount(x) sizeof((x)) / sizeof((x[0]))

const char* ANGLE_STRING = "angle";
const char* TEXTURE_STRING = "texture";
const char* MIX_COEFFICIENT_STRING = "mixCoefficient";

const char* VIEW_MATRIX_STRING = "vw_matrix";
const char* MODEL_MATRIX_STRING = "ml_matrix";
const char* PROJECTION_MATRIX_STRING = "pr_matrix";

const char* PathToSmileImage = "F:\\C++ projects\\CraftEngine\\CraftEngine\\Assets\\Sprites\\smile.bmp";
const char* PathToTileSheets = "F:\\C++ projects\\CraftEngine\\CraftEngine\\Assets\\Sprites\\lgbt.bmp";

const char* GetVertexShader()
{
	return 
R"(
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 InTexCoord1;
layout (location = 2) in vec2 InTexCoord2;

uniform mat4 pr_matrix = mat4(1.0f);
uniform mat4 vw_matrix = mat4(1.0f);
uniform mat4 ml_matrix = mat4(1.0f);

out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
	gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(pos, 1.0f);

	TexCoord1 = InTexCoord1;
	TexCoord2 = InTexCoord2;
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

uniform float mixCoefficient = 0.5f;
uniform sampler2D texture0;
uniform sampler2D texture1;

in vec2 TexCoord1;
in vec2 TexCoord2;
out vec4 color;

void main()
{
	color = mix(texture(texture0, TexCoord1), 
				texture(texture1, TexCoord2), 
				mixCoefficient);
})";
}

#define FOV				45.0f
#define ASPECT_RATIO	DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT
#define NEAR_PLANE		0.1f
#define FAR_PLANE		100.0f

class Cube : public Shape
{
public:
	Cube(std::vector<Craft::Image*> images)
	{
		Init();
		this->TexturesInit(images);
	}

	virtual void BeginDraw() override
	{
	}

	virtual void EndDraw() override
	{
	}

private: 
	void Init()
	{
		
	}
};

class CRectangle : public Shape
{
public:
	CRectangle(f32 x, f32 y, f32 w, f32 h, 
		std::vector<Craft::Image*> images)
	{
		GLfloat vertices[] =
		{
			w,    0.0f, 1.0f,		1.0f, 1.0f,		4.0f, 4.0f,	// Top Right
			w,    -h,	1.0f,		1.0f, 0.0f,		4.0f, 0.0f,	// Bottom Right
			0.0f, -h,	1.0f,		0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
			0.0f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, 4.0f,	// Top Left 
		};

		GLuint indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		SetPosition(v3{ x, y, 0.0f });

		TexturesInit(images);

		shader = new Craft::OpenGLShader(GetVertexShader(), GetFragmentShader());
		vertexArray = Craft::VertexArray::Create();
		vertexBuffer = Craft::VertexBuffer::Create(vertices, ArrayCount(vertices));
		indexBuffer = Craft::IndexBuffer::Create(indices, ArrayCount(indices));

		Craft::BufferElement pos("Position", Craft::VertexDataType::Float3);
		Craft::BufferElement textCoord1("First texture cordinates", Craft::VertexDataType::Float2);
		Craft::BufferElement textCoord2("Second texture cordinates", Craft::VertexDataType::Float2);

		Craft::BufferLayout layout( std::vector<Craft::BufferElement> {pos, textCoord1, textCoord2} );

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);
	}

	virtual void BeginDraw() override
	{
		shader->Use();
		for (s32 i = 0; i < m_Textures.size(); ++i)
		{
			m_Textures[i]->Bind(i);
			String name = TEXTURE_STRING + std::to_string(i);
			shader->SetUniform1i(name.c_str(), i);
		}

		shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ViewProjectionMatrix);
		vertexArray->Bind();
	}

	virtual void EndDraw() override
	{
		//...unbind...
	}
};

class ExampleLayer : public Craft::Layer
{
private:
	CRectangle* m_Rect;
	CRectangle* m_Rect1;

	Camera* m_Camera;
	Camera* m_Camera0;

public:
	ExampleLayer()
	{
		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		InitRenderable();
	}

	~ExampleLayer()
	{
		delete m_Rect;
	}
	
	void InitRenderable()
	{
		m_Camera = Camera::CreateOrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
		m_Camera0 = Camera::CreatePerspectiveCamera(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE,
					v3(0.0f, 0.0f, -5.0f));

		Craft::Image* smile = Craft::ImageLoader::LoadBMPImage(String(PathToSmileImage));
		Craft::Image* image = Craft::ImageLoader::LoadBMPImage(String(PathToTileSheets));

		m_Rect1 = new CRectangle(
			0.0f, 0.0f, 1.0f, 1.0f,
			std::vector<Craft::Image*> { image, smile } );

		m_Rect = new CRectangle(
			-1.0f, 0.0f, 1.0f, 1.0f,
			std::vector<Craft::Image*> { image });

		delete smile;
		delete image;
	}

	virtual void OnRender() override
	{
		RenderCommand::SetClearColor(v4 { 0.0f, 0.1f, 0.1f, 1.0f });
		RenderCommand::Clear();

		//m_Camera->SetRotation(time / 20.0f);
		Renderer::BeginScene(*m_Camera);
		Renderer::Submit(*m_Rect);
		Renderer::Submit(*m_Rect1);
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::WindowResizeEvent>(S_BIND_EVENT_FN(OnResizeWindow));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(S_BIND_EVENT_FN(OnKeyDown));
	}

	f32 nowTime = 0.0f;
	f32 lastTime = 0.0f;

	virtual void OnUpdate(f32 deltaTime) override
	{
		lastTime = nowTime;
		nowTime += deltaTime;
//		f32 rotate = Lerp(0.0, 1.0f, sinf(nowTime));

	//	m_Rect->SetRotation(rotate, v3(0.0f, 0.0f, 1.0f));
	}

private:

	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VK_F2)
		{
			ChangeCamera();
			return true;
		}

		v3 P = m_Camera->GetPosition();
		if (event.GetKeyCode() == VK_UP)
		{
			P.z+=0.1f;
		}

		if (event.GetKeyCode() == VK_DOWN)
		{
			P.z-=0.1f;
		}

		if (event.GetKeyCode() == VK_LEFT)
		{
			P.x += 0.2f;
		}

		if (event.GetKeyCode() == VK_RIGHT)
		{
			P.x -= 0.2f;
		}

		m_Camera->SetPosition(P);

		return false;
	}

	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}

	void ChangeCamera()
	{
		Camera* temp = m_Camera;
		m_Camera = m_Camera0;
		m_Camera0 = temp;
	}
};

#define CRAFT_MATH_TEST

void MathTest()
{
#ifdef CRAFT_MATH_TEST
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
#endif
}

class Sandbox : public Craft::Application
{
public:
	Sandbox(f32 fps, Craft::WindowSetting setting) : Application(fps, setting)
	{
		MathTest();
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	WindowSetting setting;
	setting.IsVSync = true;
	return new Sandbox(60.0f, setting);
}
