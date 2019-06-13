#include <Craft.h>

#define GL_GLEXT_PROTOTYPES
#include "Platform\OpenGL\OpenGL.h"
#include "Platform\OpenGL\OpenGLShader.h"

#define BIND_EVENT_FN(x) std::bind(&ExampleLayer::x, this, std::placeholders::_1)

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
		String fileName = "F:";
		byte* info = "hello world";
		bool result = Craft::FileSystem::WriteToFile(fileName, info, sizeof(info));

		//m_VertexShader = R"(#version 330 core
		//				layout (location = 0) in vec3 pos;
		//				void main()
		//				{
		//					gl_Position = vec4(pos.x, pos.y, pos.z, 1.0f);
		//				})";

		//m_FragmentShader = R"(#version 330 core
		//				out vec4 color;
		//				void main()
		//				{
		//					color = vec4(1.0f, 0.5f, 0.2f, 1.0f);
		//				})";

		//m_Shader = new Craft::OpenGLShader(m_VertexShader.c_str(), m_FragmentShader.c_str());

		const GLchar* vertexShaderSource = "#version 330 core\n"
			"layout (location = 0) in vec3 position;\n"
			"void main()\n"
			"{\n"
			"gl_Position = vec4(position.x, position.y, position.z, 1.0);\n"
			"}\0";
		const GLchar* fragmentShaderSource = "#version 330 core\n"
			"out vec4 color;\n"
			"void main()\n"
			"{\n"
			"color = vec4(0.0f, 0.0f, 0.0f, 0.0f);\n"
			"}\n\0";

		GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
		GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

		glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
		glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);

		glCompileShader(fragmentShader);
		glCompileShader(vertexShader);

		m_ShaderProgram = glCreateProgram();
		glAttachShader(m_ShaderProgram, vertexShader);
		glAttachShader(m_ShaderProgram, fragmentShader);
		glLinkProgram(m_ShaderProgram);

		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

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
		glClearColor(1.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(m_ShaderProgram);
		glBindVertexArray(m_VAO);

		glDrawArraysEXT(GL_TRIANGLES, 0, 3);

		glBindVertexArray(0);
		GLenum error = glGetError();
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