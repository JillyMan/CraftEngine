#include <Craft.h>
#include "Platform\OpenGL\OpenGL.h"
#include "Platform\OpenGL\OpenGLShader.h"

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

class ExampleLayer : public Craft::Layer
{
private:
	String m_VertexShader;
	String m_FragmentShader;
	
	Craft::Shader* m_Shader;
	
	GLfloat* m_Vertices;	
	GLuint m_VBO;
	GLuint m_VAO;

public:
	ExampleLayer()
	{
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
			-0.5f, -0.5f, 0.0f, // Left  
			0.5f, -0.5f, 0.0f, // Right 
			0.0f,  0.5f, 0.0f  // Top   
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
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(m_VAO);
		m_Shader->Use();

		glDrawArrays(GL_TRIANGLES, 0, 3);		
		
		glBindVertexArray(0);
	}

	virtual void OnEvent(Craft::Event& event) override
	{
		Craft::EventDispatcher dispatcher(event);
		dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(OnResizeWindow));
	}

	virtual void OnUpdate(f32 deltaTime) override
	{
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
	Sandbox() : Application()
	{
		PushLayer(new ExampleLayer());
	}

	virtual ~Sandbox()
	{
	}
};

Craft::Application* Craft::CreateApplication()
{
	return new Sandbox();
}