#include <map>
#include <Craft.h>

#define GAME

#ifdef GAME
	#define GL_GLEXT_PROTOTYPES
	#include "Platform\OpenGL\OpenGL.h"
	#include "Platform\OpenGL\OpenGLShader.h"
#else
	#include <iostream>
	#include "Craft\System\Vfs\VFS.h"
#endif

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

using namespace Craft;

#ifdef GAME
class ExampleLayer : public Craft::Layer
{
private:
	String m_VertexShader;
	String m_FragmentShader;
	
	GLuint m_ShaderProgram;

	Craft::Shader* m_Shader;
	
	GLfloat* m_Vertices;	
	GLuint m_VBO;
	GLuint m_VAO;

public:
	ExampleLayer()
	{
		glViewport(0, 0, DEFAULT_WINDOW_WIDTH, DEFAULT_WINDOW_HEIGHT);
		m_VertexShader = R"(#version 330 core
						layout (location = 0) in vec3 pos;
						void main()
						{
							gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
						})";
		m_FragmentShader = R"(#version 330 core
						out vec4 color;
						void main()
						{
							color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
						})";

		m_Shader = new Craft::OpenGLShader(m_VertexShader.c_str(), m_FragmentShader.c_str());

		m_Vertices = new GLfloat[9]
		{
			-0.5f, -0.5f, 0.0f, 
			0.5f, -0.5f, 0.0f, 
			0.0f,  0.5f, 0.0f  
		};

		glCreateVertexArrays(1, &m_VAO);
		glCreateBuffers(1, &m_VBO);
		glBindVertexArray(m_VAO);

		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
		glEnableVertexAttribArray(0);

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}

	~ExampleLayer()
	{
		delete m_Shader;
		glDeleteVertexArrays(1, &m_VAO);
		glDeleteBuffers(1, &m_VBO);
	}

	virtual void OnRender() override
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		m_Shader->Use();
		glBindVertexArray(m_VAO);
		glDrawArrays(GL_LINES, 0, 3);
		glBindVertexArray(0);
		GLenum error = glGetError();

		if (error > 0)
		{
			CR_ERROR("Error code [%d]", error);
		}
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(OnResizeWindow));
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