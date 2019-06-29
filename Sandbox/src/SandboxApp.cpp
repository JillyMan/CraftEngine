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
const char* RotorUniformString = "rotor";
const char* AngleUniformString = "angle";
const char* PathToTileSheets = "F:\\C++ projects\\CraftEngine\\CraftEngine\\Assets\\Sprites\\TileSheet.bmp";

const char* GetVertexShader()
{
	return 
R"(
#version 460 core
layout (location = 0) in vec3 pos;

uniform float angle;

out vec4 vertexPos;

void main()
{
	float _cos = cos(angle), _sin = sin(angle);
	float x = pos.x, y = pos.y;

	vec4 newPos = vec4(x * _cos - y * _sin,
					   x * _sin + y * _cos,
					   0.0f, 1.0f);

	gl_Position = newPos;
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

uniform vec4 vertexColour;
out vec4 color;

void main()
{
	color = vertexColour;
})";
}

class Shape
{
protected:
	Craft::v4 m_Color;
	f32 m_Angle;

	Shape(Craft::v4 color) :
		m_Color(color)
	{
	}

	virtual ~Shape() = default;

public:
	void SetColor(Craft::v4 color)
	{
		m_Color = color;
	}

	void Rotate(f32 angle)
	{
		m_Angle = angle;
	}

};

class CRectangle : public Shape
{
	GLuint m_VAO;
	VertexArrayBuffer* m_VABuffer;
	VertexBuffer* m_VBuffer;
	IndexBuffer* m_IndexBuffer;
	Shader* m_Shader;
	OpenGLTexture* m_Texture;

public:
	CRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Craft::v4 color, Image* image) : 
		Shape(color)
	{
		GLfloat vertices[] =
		{
			x1, y2, 0.0f,
			x2, y2, 0.0f,
			x1, y1, 0.0f,
			x2, y1, 0.0f,
		};

		GLuint indices[] =
		{
			0,1,2,3,1,2
		};

		m_Texture = new OpenGLTexture(
			TextureType::Texture2D, false, image);
		
		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());

		m_VABuffer = VertexArrayBuffer::Create();
		m_VBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord("Texture cordinates", VertexDataType::Float2);

		std::vector<BufferElement> i = { pos/*, textCoord*/ };
		BufferLayout layout(i);

		m_VBuffer->SetLayout(layout);
		m_VABuffer->AddVertexBuffer(m_VBuffer);
		m_VABuffer->SetIndexBuffer(m_IndexBuffer);
	}

	 void Render()
	{
		m_Shader->Use();
		m_Shader->SetUniform4f(VertexColorUniformString, m_Color);
		m_Shader->SetUniform1f(AngleUniformString, m_Angle);

		m_VABuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_VABuffer->GetCountIndices(), GL_UNSIGNED_INT, 0);
	}
};

void ImageTest()
{
	Image* image = ImageLoader::LoadBMPImage(String(PathToTileSheets));
	CR_ASSERT(image, "Can't load image path=[%s]", PathToTileSheets);
}

class ExampleLayer : public Craft::Layer
{
private:
	Shader* m_Shader;
	OpenGLVertexBuffer* m_VBuffer;
	IndexBuffer* m_IndexBuffer;

	GLuint m_VBO;
	GLuint m_VAO;
	CRectangle* rect;

public:
	ExampleLayer()
	{
		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		ImageTest();
		InitRenderable();
	}

	~ExampleLayer()
	{
		delete m_Shader;
		delete m_VBuffer;
		glDeleteVertexArrays(1, &m_VAO);
	}

	void InitRenderable()
	{
		Craft::v4 color = Craft::v4(1.0f, 0.0f, 0.0f, 1.0f);
		rect = new CRectangle(-0.5, 0.5, 0.5f, -0.5f, color);
	}

	virtual void OnRender() override
	{
		glClearColor(0.0f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		rect->Render();
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::WindowResizeEvent>(S_BIND_EVENT_FN(OnResizeWindow));
	}

	float theta = 0.0f;
	virtual void OnUpdate(f32 deltaTime) override
	{
		theta += deltaTime/1000.0f;
		float sinT = sinf(theta);
		float cosT = cosf(theta);
		Craft::v4 color;

		color.x = (sinT / 2 + 0.5f);
		color.y = (cosT / 2 + 0.5f);
		color.z = (sinT*cosT / 2 + 0.5f);

		color.w = 1.0f;

		rect->Rotate(theta);
		rect->SetColor(color);
	}

private:
	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}
};

class Sandbox : public Craft::Application
{
public:
	Sandbox(f32 fps, WindowSetting setting) : Application(60.0f, setting)
	{
		VFS_Test();
		PushLayer(new ExampleLayer());
	}

	void VFS_Test()
	{
#ifndef GAME
		bool result = VFS_Init();

		if (!result)
		{
			VFS_ErrorCode errorCode = VFS_GetLastError();
			VFS_String error;
			VFS_GetErrorString(errorCode, error);
			std::cout << error.c_str() << std::endl;
			
		}
		VFS_Shutdown();
#endif
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
