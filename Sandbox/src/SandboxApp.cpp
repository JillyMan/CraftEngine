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
//TileSheet - Copy.bmp
//const char* PathToTileSheets = "F:\\C++ projects\\CraftEngine\\CraftEngine\\Assets\\Sprites\\TileSheet.bmp";

const char* PathToTileSheets = "F:\\C++ projects\\CraftEngine\\CraftEngine\\Assets\\Sprites\\lgbt.bmp";

const char* GetVertexShader()
{
	return 
R"(
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 InTexCoord;

uniform float angle;

out vec2 TexCoord;

void main()
{
	float _cos = cos(angle), _sin = sin(angle);
	float x = pos.x,
		  y = pos.y;

	vec4 newPos = vec4(pos, 1.0f); /*vec4(x * _cos - y * _sin,
					   x * _sin + y * _cos,
					   0.0f, 1.0f);*/

	TexCoord = InTexCoord;
	gl_Position = newPos;
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

uniform vec4 vertexColour;
uniform sampler2D outTexture;

in vec2 TexCoord;
out vec4 color;

void main()
{
	color = texture(outTexture, TexCoord) ;
})";
}

Image* GetTestImage()
{
	static Image* image = ImageLoader::LoadBMPImage(String(PathToTileSheets));
	BitmapHeader* bitmap = image->GetFormatData<BitmapHeader>();
	BITMAPINFO* info = image->GetFormatData<BITMAPINFO>();

	CR_ASSERT(image, "Can't load image path=[%s]", PathToTileSheets);
	return image;
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
	Shader* m_Shader;
	Texture* m_Texture;

	VertexArrayBuffer* m_VABuffer;
	VertexBuffer* m_VBuffer;
	IndexBuffer* m_IndexBuffer;

	GLuint m_TextureId;

public:
	CRectangle(f32 x1, f32 y1, f32 x2, f32 y2, Craft::v4 color, Image* image) : 
		Shape(color)
	{
		GLfloat vertices[] =
		{
			0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
			0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		//x1, y2, 0.0f, 0.0f, 0.0f,
		//x2, y2, 0.0f, 1.0f, 0.0f,
		//x1, y1, 0.0f, 0.0f, 1.0f,
		//x2, y1, 0.0f, 1.0f, 1.0f,

		GLuint indices[] =
		{
			//0,1,2,3,1,2
			0, 1, 3,
			1, 2, 3
		};
		
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// Set texture wrapping to GL_REPEAT (usually basic wrapping method)
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->Width, image->Height, 0, GL_BGR, GL_UNSIGNED_BYTE, image->Pixels);
		glGenerateMipmap(GL_TEXTURE_2D);

		//m_Texture = new OpenGLTexture(TextureType::Texture2D, image, true);
		//m_Texture->Bind();
		//m_Texture->SetParameteri(TextureParameterName::S, TextureParameter::Repeat);
		//m_Texture->SetParameteri(TextureParameterName::T, TextureParameter::Repeat);
		//m_Texture->Unbind();

		m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());

		m_VABuffer = VertexArrayBuffer::Create();
		m_VBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
		m_IndexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));

		BufferElement pos("Position", VertexDataType::Float3);
		BufferElement textCoord("Texture cordinates", VertexDataType::Float2);

		BufferLayout layout( std::vector<BufferElement> {pos, textCoord} );

		m_VBuffer->SetLayout(layout);
		m_VABuffer->AddVertexBuffer(m_VBuffer);
		m_VABuffer->SetIndexBuffer(m_IndexBuffer);
	}

	 void Render()
	{
		//m_Texture->Bind();
		 glBindTexture(GL_TEXTURE_2D, m_TextureId);
		m_Shader->Use();
		//m_Shader->SetUniform4f(VertexColorUniformString, m_Color);
		//m_Shader->SetUniform1f(AngleUniformString, m_Angle);

		m_VABuffer->Bind();
		glDrawElements(GL_TRIANGLES, m_VABuffer->GetCountIndices(), GL_UNSIGNED_INT, 0);
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
		Craft::v4 color = Craft::v4(1.0f, 0.0f, 0.0f, 1.0f);
		rect = new CRectangle(-0.5, 0.5, 0.5f, -0.5f, color, GetTestImage());
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
