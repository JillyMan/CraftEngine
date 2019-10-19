#include <map>
#include <Craft.h>
#include <Craft\InputHandler.h>
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

#define ArrayCount(x) sizeof((x)) / sizeof((x[0]))

#define FOV				45.0f
#define ASPECT_RATIO	DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT
#define NEAR_PLANE		0.1f
#define FAR_PLANE		100.0f

const char* ANGLE_STRING = "angle";
const char* TEXTURE_STRING = "texture";
const char* MIX_COEFFICIENT_STRING = "mixCoefficient";
const char* U_COLOR_STRING = "u_color";

const char* VIEW_MATRIX_STRING = "vw_matrix";
const char* MODEL_MATRIX_STRING = "ml_matrix";
const char* PROJECTION_MATRIX_STRING = "pr_matrix";

String BaseSpritesFolder = "C:\\Users\\Artsiom\\Documents\\Projects\\CraftEngine\\Assets\\Sprites\\";
String PathToSmileImage = BaseSpritesFolder + "smile.bmp";
String PathToTileSheets = BaseSpritesFolder + "lgbt.bmp";

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
uniform vec4 u_color = vec4(1.0f, 1.0f, 1.0f, 1.0f);

in vec2 TexCoord1;
in vec2 TexCoord2;
out vec4 color;

void main()
{
	color = u_color * mix(texture(texture0, TexCoord1), 
				texture(texture1, TexCoord2), 
				mixCoefficient);
})";
}


class Cube : public Shape
{
public:
	Cube(f32 x, f32 y, std::vector<Craft::Image*> images)
	{
		Init();
		SetPosition(v3(x, y, 0.0f));
		this->TexturesInit(images);
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

		shader->SetUniform4f(U_COLOR_STRING, v4(1.0f, 0.0f, 0.0f, 1.0f));
		shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ViewProjectionMatrix);

		vertexArray->Bind();
	}

	virtual void EndDraw() override
	{
	}

private: 
	void Init()
	{
		f32 vertices[] = {
			//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			//0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
			//0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			//0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			//-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
			//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			//0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			//0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			//0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
			//-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
			//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			//-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			//-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			//0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			//0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			//0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			//0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
			//0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			//0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
			//-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
			//-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
			//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
			// 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
			// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			// 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
			//-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
			//-0.5f,  0.5f, -0.5f,  0.0f, 1.0f

			0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
			1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
			0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
			1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
		};

		u32 indices[] = {
			0, 2, 1, //face front
			0, 3, 2,
			2, 3, 4, //face top
			2, 4, 5,
			1, 2, 5, //face right
			1, 5, 6,
			0, 7, 4, //face left
			0, 4, 3,
			5, 4, 7, //face back
			5, 7, 6,
			0, 6, 7, //face bottom
			0, 1, 6
		};

		shader = new Craft::OpenGLShader(GetVertexShader(), GetFragmentShader());
		vertexArray = Craft::VertexArray::Create();
		vertexBuffer = Craft::VertexBuffer::Create(vertices, ArrayCount(vertices));
		indexBuffer = Craft::IndexBuffer::Create(indices, ArrayCount(indices));

		Craft::BufferElement pos("Position", Craft::VertexDataType::Float3);
		Craft::BufferElement textCoord1("First texture cordinates", Craft::VertexDataType::Float2);

		Craft::BufferLayout layout(std::vector<Craft::BufferElement> { pos, textCoord1 });

		vertexBuffer->SetLayout(layout);
		vertexArray->AddVertexBuffer(vertexBuffer);
		vertexArray->SetIndexBuffer(indexBuffer);
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
			w,    0.0f, 1.0f,		1.0f, 1.0f,		1.0f, 1.0f,	// Top Right
			w,    -h,	1.0f,		1.0f, 0.0f,		1.0f, 0.0f,	// Bottom Right
			0.0f, -h,	1.0f,		0.0f, 0.0f,		0.0f, 0.0f,	// Bottom Left
			0.0f, 0.0f, 1.0f,		0.0f, 1.0f,		0.0f, 1.0f,	// Top Left 
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

class ExampleScene : public Craft::Layer
{
private:
	Shape* m_Rect;
	Shape* m_Rect1;
	Shape* m_Cube;

	Camera* m_Camera;
	Camera* m_Camera0;

public:
	ExampleScene()
	{
		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		InitRenderable();
	}

	~ExampleScene()
	{
		delete m_Rect;
	}
	
	void InitRenderable()
	{
		RenderCommand::ZTest(true);
		RenderCommand::SetClearColor(v4{ 0.0f, 0.1f, 0.1f, 1.0f });

		m_Camera = Camera::CreateOrthographicCamera(-1.6f, 1.6f, -0.9f, 0.9f);
		m_Camera0 = Camera::CreatePerspectiveCamera(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE,
					v3(0.0f, 0.0f, -5.0f));

		Craft::Image* smile = Craft::ImageLoader::LoadBMPImage(PathToSmileImage);
		Craft::Image* image = Craft::ImageLoader::LoadBMPImage(PathToTileSheets);

		m_Rect1 = new CRectangle(
			-2.0f, 0.0f, 1.0f, 1.0f,
			std::vector<Craft::Image*> { image, smile } );
		m_Rect1->SetRotation(-75.0f, v3(1.0f, 0.0f, 0.0f));

		m_Rect = new CRectangle(
			-1.0f, 0.0f, 1.0f, 1.0f,
			std::vector<Craft::Image*> { image });

		m_Cube = new Cube(0.0f, 0.0f, std::vector<Craft::Image*> { smile });
		m_Cube->SetRotation(55.0f, v3(0.0f, 0.0f, 1.0f));

		delete smile;
		delete image;
	}

	virtual void OnRender() override
	{
		RenderCommand::Clear();

		Renderer::BeginScene(*m_Camera);

		Renderer::Submit(*m_Rect);
		Renderer::Submit(*m_Rect1);
		Renderer::Submit(*m_Cube);
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(ExampleScene::OnMouseMove));
		dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(ExampleScene::OnResizeWindow));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(ExampleScene::OnKeyDown));
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
		v3 P = m_Camera->GetPosition();
		v3 force = v3 { 0.01f, 0.01f, 0.01f } * deltaTime;

		if (Input::InputHandler::IsKeyPressed('W'))
		{
			P.z += force.z;
		}

		if (Input::InputHandler::IsKeyPressed('S'))
		{
			P.z -= force.z;
		}

		if (Input::InputHandler::IsKeyPressed('A'))
		{
			P.x += force.x;
		}

		if (Input::InputHandler::IsKeyPressed('D'))
		{
			P.x -= force.x;
		}

		if (Input::InputHandler::IsKeyPressed('Z'))
		{
			P.y -= force.y;
		}

		if (Input::InputHandler::IsKeyPressed('Q'))
		{
			P.y += force.y;
		}

		m_Camera->SetPosition(P);

		static f32 lastTime;
		lastTime += deltaTime;

		m_Cube->SetRotation(lastTime/20.0f, v3(1.0, 0.0, 0.0f));
	}

private:
	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VK_F2)
		{
			ChangeCamera();
			return true;
		}

		if (event.GetKeyCode() == VK_ESCAPE)
		{		
			Sleep(1000);
			exit(1);
		}

		return false;
	}

	bool OnMouseMove(Craft::MouseMovedEvent& e)
	{
		//static f32 LastY = e.y;
		//v3 P = m_Camera->GetPosition();
		//f32 y = P.y - LastY;
		//LastY += ;
		return true;
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
#ifndef CRAFT_MATH_TEST
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
		PushLayer(new ExampleScene());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	WindowSetting setting;
	setting.IsVSync = false;
	return new Sandbox(60.0f, setting);
}
