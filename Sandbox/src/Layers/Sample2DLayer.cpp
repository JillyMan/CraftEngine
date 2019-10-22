#include "crpch.h"
#include "Sample2DLayer.h"

#include <Craft/Graphics/RenderCommand.h>

#include <Craft/InputHandler.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/Primitives/Sprite.h>

Sample2DLayer::Sample2DLayer() 
{
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 0.1f, 0.1f, 1.0f));
	m_Camera = Craft::Camera::CreateOrthographicCamera(
		-16.0, 16.0f, -9.0f, 9.0f, 0.1f, 1000.0f);
	
	f32 w = 1.0f, h = 1.0f;

	GLfloat vertices[] =
	{
		w,    0.0f, 1.0f, // Top Right
		w,    -h,	1.0f, // Bottom Right
		0.0f, -h,	1.0f, // Bottom Left
		0.0f, 0.0f, 1.0f, // Top Left 
	};

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	m_VertexArray = Craft::Graphics::VertexArray::Create();

	Craft::Graphics::IndexBuffer* indexBuffer = Craft::Graphics::IndexBuffer::Create(indices, ArrayCount(indices));
	Craft::Graphics::VertexBuffer* vertexBuffer = Craft::Graphics::VertexBuffer::Create(vertices, ArrayCount(vertices));

	Craft::Graphics::BufferElement pos("Position", Craft::Graphics::VertexDataType::Float3);
	Craft::Graphics::BufferLayout layout(std::vector<Craft::Graphics::BufferElement> { pos });

	vertexBuffer->SetLayout(layout);
	m_VertexArray->AddVertexBuffer(vertexBuffer);
	m_VertexArray->SetIndexBuffer(indexBuffer);

	m_Shader = new Craft::Graphics::OpenGLShader(Craft::Graphics::GetSimpleVertexShader(), Craft::Graphics::GetFragmentColorShader());
}

Sample2DLayer::~Sample2DLayer()
{
	delete m_Camera;
}

void Sample2DLayer::OnEvent(Craft::Event& event) 
{
	Craft::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Sample2DLayer::OnKeyDown));
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Sample2DLayer::OnResizeWindow));
	dispatcher.Dispatch<Craft::MouseScrollWheelEvent>(BIND_EVENT_FN(Sample2DLayer::OnMouseWheelScroll));
}

void Sample2DLayer::OnRender() 
{
	Craft::Graphics::RenderCommand::Clear();
	Craft::Graphics::Renderer::BeginScene(*m_Camera);
	
	Craft::mat4 scale = Craft::mat4::Scale(Craft::v3(0.5f, 0.5f, 0.5f));

	m_Shader->Use();
	m_Shader->SetUniform3f("u_color", m_Color);

	for (int y = 0; y < 20.0f; ++y)
	{
		for (int x = 0; x < 50.0f; ++x)
		{
			Craft::v3 pos(x * 0.6f, y * 0.6f, 1.0f);
			Craft::mat4 transform = Craft::mat4::Translate(pos) * scale;
			Craft::Graphics::Renderer::Submit(m_VertexArray, m_Shader, transform);
		}
	}
}

void Sample2DLayer::OnUpdate(f32 dt)
{
	Craft::v3 P = m_Camera->GetPosition();
	f32 cameraSpeed = 0.05f * dt;

	if (Craft::Input::InputHandler::IsKeyPressed('W')) 
	{
		P.y -= cameraSpeed;
	}
	if (Craft::Input::InputHandler::IsKeyPressed('S')) 
	{
		P.y += cameraSpeed;
	}
	if (Craft::Input::InputHandler::IsKeyPressed('A')) 
	{
		P.x += cameraSpeed;
	}
	if (Craft::Input::InputHandler::IsKeyPressed('D')) 
	{
		P.x -= cameraSpeed;
	}

	m_Camera->SetPosition(P);
}

bool Sample2DLayer::OnKeyDown(Craft::KeyPressedEvent& event)
{
	if (event.GetKeyCode() == VK_ESCAPE)
	{
		exit(1);
	}

	return false;
}

bool Sample2DLayer::OnResizeWindow(Craft::WindowResizeEvent& event) {
	//todo: move to renderer static method!!
	glViewport(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}

bool Sample2DLayer::OnMouseWheelScroll(Craft::MouseScrollWheelEvent& event)
{
	s32 offset = event.GetZDelta();
	offset /= abs(offset);

	Craft::v3 s = m_Camera->GetScale();
	s += 0.2f * offset;
	m_Camera->SetScale(s);

	return true;
}