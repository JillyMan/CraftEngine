#include <map>
#include <Craft.h>
#include <Craft\InputHandler.h>
#include <Craft\Graphics\Renderer.h>
#include <Craft\Graphics\RendererAPI.h>
#include <Craft\Graphics\RenderCommand.h>

#include <Craft\Graphics\Cameras\Camera.h>

#include <Craft\Graphics\Texture.h>
#include <Craft\Graphics\Image\ImageLoader.h>

//------ PLATFORM CODE -------
#include <Platform\OpenGL\OpenGL.h>
#include <Platform\OpenGL\OpenGLShader.h>
#include <Platform\OpenGL\OpenGLBuffer.h>
#include <Platform\OpenGL\OpenGLTexture.h>
#include <Platform\OpenGL\OpenGLVertexArray.h>
#include <Platform\OpenGL\OpenGLRendererAPI.h>
//----------------------------

using namespace Craft;
using namespace Graphics;

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
	Cube(v3 pos, Image* image) : 
		Shape(pos, *image)
	{
		Init();
		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
	}

	virtual void BeginDraw() override
	{
		m_Shader->Use();
		m_VertexArray->Bind();

		m_Texture->Bind(0);

		String name(TEXTURE_STRING);
		name.append("0");

		m_Shader->SetUniform1i(name.c_str(), 0);

		m_Shader->SetUniform4f(U_COLOR_STRING, v4(1.0f, 0.0f, 0.0f, 1.0f));
		m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ViewProjectionMatrix);
	}

	virtual void EndDraw() override
	{
	}

private: 
	void Init()
	{
		//m_Mesh = Mesh::GenerateCubeWithTextureCoord();


		f32 vertices[] = {
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

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);
		BufferLayout layout(std::vector<BufferElement> { pos, textCoord1 });

		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
		vertexBuffer->SetLayout(layout);

		m_VertexArray = VertexArray::Create();
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		
		m_VertexArray->SetIndexBuffer(
			IndexBuffer::Create(indices, ArrayCount(indices))
		);
	}
};

class Sprite : public Shape
{
public:
	Sprite(f32 x, f32 y, f32 w, f32 h, Image& image) : 
		Shape(v3(x, y, 0.0f), image)
	{
		SetPosition(v3(x, y, 0.0f));
		InitVertices(x, y, w, h);
		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
	}

	virtual void BeginDraw() override
	{
		m_Shader->Use();
		m_Texture->Bind(0);
		String name(TEXTURE_STRING);
		name.append("0");
		m_Shader->SetUniform1i(name.c_str(), 0);

		m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
		m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ViewProjectionMatrix);
		m_VertexArray->Bind();
	}

	virtual void EndDraw() override
	{
		//...unbind...
	}

	void InitVertices(f32 x, f32 y, f32 w, f32 h)
	{
		GLfloat vertices[] =
		{
			w,    0.0f, 1.0f,	1.0f, 1.0f,	// Top Right
			w,    -h,	1.0f,	1.0f, 0.0f,	// Bottom Right
			0.0f, -h,	1.0f,	0.0f, 0.0f,	// Bottom Left
			0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// Top Left 
		};

		GLuint indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		m_VertexArray = VertexArray::Create();

		IndexBuffer* indexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));
		VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);

		BufferLayout layout(std::vector<BufferElement> {pos, textCoord1 });

		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);
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

		m_Camera = Camera::CreateOrthographicCamera(-1.6f, 1.6f, -1.9f, 1.9f);
		m_Camera0 = Camera::CreatePerspectiveCamera(FOV, ASPECT_RATIO, NEAR_PLANE, FAR_PLANE,
					v3(0.0f, 0.0f, -5.0f));

		Craft::Image* smile = Craft::ImageLoader::LoadBMPImage(PathToSmileImage);
		Craft::Image* image = Craft::ImageLoader::LoadBMPImage(PathToTileSheets);

		m_Rect1 = new Sprite(
			-2.0f, 0.0f, 1.0f, 1.0f, 
			*image);
		m_Rect1->SetRotation(-75.0f, v3(1.0f, 0.0f, 0.0f));

		m_Rect = new Sprite(
			-2.0f, 0.0f, 1.0f, 1.0f,
			*smile);

		m_Rect->SetRotation(45.0f, v3(0.0f, 1.0f, 0.0f));

		m_Cube = new Cube(v3(0.0f, 0.0f, 1.0f), smile);
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
		UpdataCamera(deltaTime);
		UpdataShapes(deltaTime);
	}

	void UpdataShapes(f32 deltaTime) 
	{
		static f32 lastTime;
		lastTime += deltaTime;
		m_Cube->SetRotation(lastTime / 20.0f, v3(1.0, 0.0, 0.0f));
	}

	void UpdataCamera(f32 deltaTime)
	{
		v3 P = m_Camera->GetPosition();
		v3 force = v3{ 0.01f, 0.01f, 0.01f } *deltaTime;

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
