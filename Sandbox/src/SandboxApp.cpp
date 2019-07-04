#include <map>
#include <Craft.h>

#define GAME

#ifdef GAME
	#define GL_GLEXT_PROTOTYPES
	#include "Platform\OpenGL\OpenGL.h"
	#include "Platform\OpenGL\OpenGLShader.h"
	#include "Platform\OpenGL\OpenGLBuffer.h"
	#include "Craft\Graphics\Texture.h"
	#include "Craft\Graphics\Image\ImageLoader.h"
	#include "Platform\OpenGL\OpenGLTexture.h"
	#include "Platform\OpenGL\OpenGLVertexArrayBuffer.h"
#else
	#include <iostream>
	#include "Craft\System\Vfs\VFS.h"
#endif

using namespace Craft;

#define S_BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)
#define ArrayCount(x) sizeof((x)) / sizeof((x[0]))

const char* VertexColorUniformString = "vertexColour";
const char* ROTOR_STRING = "rotor";
const char* ANGLE_STRING = "angle";
const char* MIX_COEFFICIENT_STRING = "mixCoefficient";
const char* TRANSFORM_STRING = "transform";

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

uniform mat4 transform;

out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
	gl_Position = transform * vec4(pos, 1.0f);

	TexCoord1 = InTexCoord1;
	TexCoord2 = InTexCoord2;
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

uniform float mixCoefficient;
uniform sampler2D texture0;
uniform sampler2D texture1;

in vec2 TexCoord1;
in vec2 TexCoord2;
out vec4 color;

void main()
{
	color = mix(texture(texture0, TexCoord1), 
				texture(texture1, vec2(1.0f - TexCoord2.x, TexCoord2.y)), 
				mixCoefficient);
})";
}

class Shape
{
protected:
	Craft::v4 m_Color;
	f32 m_Angle = 0.0f;
	f32 m_MixCoeff = 0.5f;
	mat4 m_TransformMatrix;

	Craft::VertexArrayBuffer* m_VABuffer;
	Craft::VertexBuffer* m_VBuffer;
	Craft::IndexBuffer* m_IndexBuffer;

	Craft::Shader* m_Shader;
	std::vector<Craft::Texture*> m_Textures;

	Shape(Craft::v4 color) :
		m_Color(color), 
		m_TransformMatrix(mat4::Identity())
	{
	}

	virtual ~Shape() = default;

public:
	void SetColor(Craft::v4 color)
	{
		m_Color = color;
	}

	void SetTransform(mat4 transformMatrix)
	{
		m_TransformMatrix = transformMatrix;
	}

	void Rotate(f32 angle)
	{
		m_Angle = angle;
	}

	void SetMixCoeff(float mixCoeff)
	{
		m_MixCoeff = mixCoeff;
	}
};

class CRectangle : public Shape
{
public:
	CRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Craft::v4 color, std::vector<Craft::Image*> images) :
		Shape(color)
	{
		GLfloat vertices[] =
		{
			0.5f,  0.5f, 0.0f,		1.0f, 1.0f,		2.0f, 2.0f,
			0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		2.0f, 0.0f,
			-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 2.0f,
		};

		GLuint indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		TexturesInit(images);

		m_Shader = new Craft::OpenGLShader(GetVertexShader(), GetFragmentShader());
		m_VABuffer = Craft::VertexArrayBuffer::Create();
		m_VBuffer = Craft::VertexBuffer::Create(vertices, ArrayCount(vertices));
		m_IndexBuffer = Craft::IndexBuffer::Create(indices, ArrayCount(indices));

		Craft::BufferElement pos("Position", Craft::VertexDataType::Float3);
		Craft::BufferElement textCoord1("First texture cordinates", Craft::VertexDataType::Float2);
		Craft::BufferElement textCoord2("Second texture cordinates", Craft::VertexDataType::Float2);

		Craft::BufferLayout layout( std::vector<Craft::BufferElement> {pos, textCoord1, textCoord2} );

		m_VBuffer->SetLayout(layout);
		m_VABuffer->AddVertexBuffer(m_VBuffer);
		m_VABuffer->SetIndexBuffer(m_IndexBuffer);
	}

	void Render()
	{
		m_Shader->Use();
		for (s32 i = 0; i < m_Textures.size(); ++i)
		{
			m_Textures[i]->Bind(i);
			String name = "texture" + std::to_string(i);
			m_Shader->SetUniform1i(name.c_str(), i);
		}
		
		m_Shader->SetUniform1f(MIX_COEFFICIENT_STRING, m_MixCoeff);
		m_Shader->SetUniformMatrix4fv(TRANSFORM_STRING, m_TransformMatrix);

		m_VABuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_VABuffer->GetCountIndices(), GL_UNSIGNED_INT, 0);
	}

	~CRectangle()
	{

		for (s32 i = 0; i < m_Textures.size(); ++i)
		{
			delete m_Textures[i];
		}

		delete m_Shader;
		delete m_VABuffer;
		delete m_VBuffer;
		delete m_IndexBuffer;
	}

private:
	void TexturesInit(std::vector<Craft::Image*> images)
	{
		for(Craft::Image* image : images)
		{ 
			Craft::Texture* texture = Craft::Texture::Create(Craft::TextureType::Texture2D);
			texture->Bind();
			texture->SetParameteri(Craft::TextureParameterName::MinFilter, Craft::TextureParameter::Linear);
			texture->SetParameteri(Craft::TextureParameterName::MagFilter, Craft::TextureParameter::Linear);
			texture->SetImage(*image);
			m_Textures.push_back(texture);
		}
	}
};

struct Camera
{
	mat4 transform;

	Camera() :
		transform(mat4::Identity())
	{
	}

	void Move(v3 dir)
	{
		transform += mat4::Translate(dir);
	}

	void Update(f32 dt)
	{
	}
};

class ExampleLayer : public Craft::Layer
{
private:
	CRectangle* m_Rect;

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
		Craft::Image* smile = Craft::ImageLoader::LoadBMPImage(String(PathToSmileImage));
		Craft::Image* image = Craft::ImageLoader::LoadBMPImage(String(PathToTileSheets));

		Craft::v4 color = Craft::v4(1.0f, 0.0f, 0.0f, 1.0f);
		m_Rect = new CRectangle(-0.5, 0.5, 0.5f, -0.5f, color, std::vector<Craft::Image*> { smile, image } );

		delete smile;
		delete image;
	}
	
	virtual void OnRender() override
	{
		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Rect->Render();
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::WindowResizeEvent>(S_BIND_EVENT_FN(OnResizeWindow));
		dispatcher.Dispatch<Craft::KeyPressedEvent>(S_BIND_EVENT_FN(OnKeyDown));
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
		if (moved)
		{
			m_Camera.Update(deltaTime);
			m_Rect->SetTransform(m_Camera.transform);
			moved = false;
		}
	}

private:
	Camera m_Camera;
	bool moved = false;

	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		v3 dir = {};
		if (event.GetKeyCode() == VK_UP)
		{
			dir.y = -1.0f;
		}

		if (event.GetKeyCode() == VK_DOWN)
		{
			dir.y = 1.0f;
		}

		m_Camera.Move(dir);
		moved = true;
		return moved;
	}

	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}
};

void MathTest()
{
	Craft::v3 a{ 1,2,3 };
	Craft::v3 b{ 1,2,3 };
	Craft::v3 c = a + b;
	std::cout << "A:			" << a << std::endl;
	std::cout << "B:			" << b << std::endl;
	std::cout << "Dot a*b:      " << Dot(a, b)		<< std::endl;
	std::cout << "Cross a^b:    " << Cross(a, b)	<< std::endl;
	std::cout << "Scalar a+10:  " << (a + 10.0f)	<< std::endl;
	std::cout << "c = a + b:    " << (a + b)		<< std::endl;
	std::cout << "Length(c):    " << Length(c)		<< std::endl;
	std::cout << "Normalize(c): " << Normalize(c)	<< std::endl;

	mat4 mat0 = mat4::Identity(1.0);
	mat4 mat1 = mat4::Identity(2.0);
	mat4 mat2 = mat0 + mat1;

	std::cout << "math: " << "\n" << mat2 << std::endl;
}

class Sandbox : public Craft::Application
{
public:
	Sandbox(f32 fps, Craft::WindowSetting setting) : Application(60.0f, setting)
	{
		PushLayer(new ExampleLayer());
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
