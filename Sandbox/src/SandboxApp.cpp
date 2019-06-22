#include <map>
#include <Craft.h>

#define GAME

#ifdef GAME
	#define GL_GLEXT_PROTOTYPES
	#include "Platform\OpenGL\OpenGL.h"
	#include "Platform\OpenGL\OpenGLShader.h"
	#include "Platform\OpenGL\OpenGLBuffer.h"
#else
	#include <iostream>
	#include "Craft\System\Vfs\VFS.h"
#endif

using namespace Craft;

#define S_BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)


/* shader data types

where n - [1,4]
	vec"n"  - just vector
	bvec"n" - boolean
	ivec"n" - integer
	uvec"n" - uinsigend integer 
	dvec"n" - double

For access to element can use
	vec v;
	v.x, v.y, v.z, v.w		or 
	v.r, v.g, v.b, v.a		or
	v.s, v.t, v.p, v.q

*/

const char* GetVertexShader()
{
	return 
R"(
#version 460 core
layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 colour;

out vec4 vertexColour;

void main()
{
	gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
	vertexColour = vec4(colour, 1.0f);
})";
}

const char* GetFragmentShader()
{
	return 
R"(
#version 460 core

in vec4 vertexColour;
out vec4 color;

void main()
{
	color = vertexColour;
})";
}

enum class ShaderDataType
{
	None = 0,
	Float,
	Float2,
	Float3,
	Float4,
	Mat3,
	Mat4,
	Int,
	Int2,
	Int3,
	Int4,
	Bool
};

u32 ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
		case ShaderDataType::Float:		return 4;
		case ShaderDataType::Float2:	return 4 * 2;
		case ShaderDataType::Float3:	return 4 * 3;
		case ShaderDataType::Float4:	return 4 * 4;
		case ShaderDataType::Mat3:		return 4 * 3 * 3;
		case ShaderDataType::Mat4:		return 4 * 4 * 4;
		case ShaderDataType::Int:		return 4;
		case ShaderDataType::Int2:		return 4 * 2;
		case ShaderDataType::Int3:		return 4 * 3;
		case ShaderDataType::Int4:		return 4 * 4;
		case ShaderDataType::Bool:		return 1;
	}

	CR_ASSERT(false, "Invalid ShaderDataType");
	return 0;
}

struct BufferAttrib
{
};

class VertexArrayBuffer
{
public:

	VertexArrayBuffer()
	{
		glCreateVertexArrays(1, &m_BufferId);
	}

	void Bind()
	{
		glBindVertexArray(m_BufferId);
	}

	void Unbind()
	{
		glBindVertexArray(0);
	}

private:
	
	GLuint m_BufferId;
	std::vector<VertexBuffer*> m_VerticesBuffer;
	IndexBuffer* m_IndexBuffer;
};

class CRectangle
{
	GLuint m_VAO;
	OpenGLVertexBuffer* m_VBuffer;
	IndexBuffer* m_IndexBuffer;
	Shader* m_Shader;

public:

	CRectangle(f32 x1, f32 y1, f32 x2, f32 y2)
	{
		GLfloat vertices[] =
		{
			x1, y2, 0.0f, 1.0f, 0.0f, 0.0f,
			x2, y2, 0.0f, 0.0f, 1.0f, 0.0f,
			x1, y1, 0.0f, 0.0f, 0.0f, 1.0f,
			x2, y1, 0.0f, 1.0f, 0.0f, 0.0f,
		};

		m_Shader = new Craft::OpenGLShader(GetVertexShader(), GetFragmentShader());

		glCreateVertexArrays(1, &m_VAO);
		glBindVertexArray(m_VAO);

		m_VBuffer = new OpenGLVertexBuffer(vertices, sizeof(vertices));
		m_VBuffer->SetAttrib(3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat));
		m_VBuffer->SetAttrib(3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));

		GLuint indices[] = 
		{
			0,1,2,3,1,2
		};

		m_IndexBuffer = IndexBuffer::Create(indices, sizeof(indices));

		glBindVertexArray(0);
	}

	void Render()
	{
		m_Shader->Use();
		glBindVertexArray(m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
};

#ifdef GAME
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
		rect = new CRectangle(-0.5, 0.5, 0.5f, -0.5f);
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
		theta += deltaTime;
	}

private:
	bool OnResizeWindow(Craft::WindowResizeEvent& event)
	{
		glViewport(0, 0, event.GetWidth(), event.GetHeight());
		return true;
	}
};
#endif

class Sandbox : public Craft::Application
{
public:
	Sandbox() : Application()
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
	return new Sandbox();
}
