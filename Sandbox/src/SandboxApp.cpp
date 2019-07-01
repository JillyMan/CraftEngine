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

uniform float angle;

out vec2 TexCoord1;
out vec2 TexCoord2;

void main()
{
	float _cos = cos(angle), _sin = sin(angle);
	float x = pos.x,
		  y = pos.y;

	//vec4 newPos = vec4(pos, 1.0f); /*vec4(x * _cos - y * _sin,
	//				   x * _sin + y * _cos,
	//				   0.0f, 1.0f);*/

	vec4 newPos = vec4(x * _cos - y * _sin,
					   x * _sin + y * _cos,
					   0.0f, 1.0f);

	TexCoord1 = InTexCoord1;
	TexCoord2 = InTexCoord2;
	gl_Position = newPos;
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

	VertexArrayBuffer* m_VABuffer;
	VertexBuffer* m_VBuffer;
	IndexBuffer* m_IndexBuffer;

	Shader* m_Shader;
	std::vector<Texture*> m_Textures;

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

	void SetMixCoeff(float mixCoeff)
	{
		m_MixCoeff = mixCoeff;
	}
};

class CRectangle : public Shape
{
public:
	CRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Craft::v4 color, std::vector<Image*> images) : 
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

		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
		m_VABuffer = VertexArrayBuffer::Create();
		m_VBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);
		BufferElement textCoord2("Second texture cordinates", VertexDataType::Float2);

		BufferLayout layout( std::vector<BufferElement> {pos, textCoord1, textCoord2} );

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
		m_Shader->SetUniform1f(ANGLE_STRING, m_Angle);

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
	void TexturesInit(std::vector<Image*> images)
	{
		for(Image* image : images)
		{ 
			Texture* texture = Texture::Create(TextureType::Texture2D);
			texture->Bind();
			texture->SetParameteri(TextureParameterName::MinFilter, TextureParameter::Linear);
			texture->SetParameteri(TextureParameterName::MagFilter, TextureParameter::Linear);
			texture->SetImage(*image);
			m_Textures.push_back(texture);
		}
	}
};

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
		Image* smile = ImageLoader::LoadBMPImage(String(PathToSmileImage));
		Image* image = ImageLoader::LoadBMPImage(String(PathToTileSheets));

		Craft::v4 color = Craft::v4(1.0f, 0.0f, 0.0f, 1.0f);
		rect = new CRectangle(-0.5, 0.5, 0.5f, -0.5f, color, std::vector<Image*> { smile, image } );

		delete smile;
		delete image;
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
		dispatcher.Dispatch<Craft::KeyPressedEvent>(S_BIND_EVENT_FN(OnKeyDown));

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

		//rect->Rotate(theta);
		rect->SetColor(color);
	}

private:
	f32 mixCoeff = 0.5f;
	f32 speedMix = 0.05f;

	bool OnKeyDown(Craft::KeyPressedEvent& event)
	{
		if (event.GetKeyCode() == VK_UP)
		{
			mixCoeff += speedMix;
		}

		if (event.GetKeyCode() == VK_DOWN)
		{
			mixCoeff -= speedMix;
		}

		rect->SetMixCoeff(mixCoeff);
		return true;
	}

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
