#include "crpch.h"
#include "Sample2DLayer.h"

#include <Craft/Core/Application.h>
#include <Craft/Graphics/RenderCommand.h>
#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/Primitives/Sprite.h>

#include <imgui.h>

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

	m_PlayerPos = Craft::v3(0.0f, 0.0f, 0.0f);

	GLuint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};

	m_Player = { };
	m_Player.A = { 0.0f, -0.98f, 0.0f };
	m_Player.V = { -0.5f, 5.0f, 0.0f };
	m_Player.P = { 0.0f, 0.0f, 1.0f };

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


void Sample2DLayer::OnDebugRender()
{
	ImGui::Begin("2D game settings");
	ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 100.0f);
	ImGui::SliderFloat("Scale", &m_ScaleRatio, 0.0f, 3.0f);
	ImGui::ColorPicker3("Tiles color", m_Color.e);
	ImGui::End();
}

void Sample2DLayer::OnRender()
{
	Craft::Graphics::RenderCommand::Clear();
	Craft::Graphics::Renderer::BeginScene(*m_Camera);

	m_Shader->Use();
	m_Shader->SetUniform3f("u_color", m_Color);

	Craft::mat4 scaleMat = Craft::mat4::Scale(Craft::v3(m_ScaleRatio));
	Craft::mat4 transofrm = Craft::mat4::Translate(m_Player.P) * scaleMat;
	Craft::Graphics::Renderer::Submit(m_VertexArray, m_Shader, transofrm);
}

void Sample2DLayer::OnUpdate(f32 dt)
{
	UpdateCamera(m_Camera, dt);
	UpdatePlayer(dt);
}


static void UpdateCamera(Craft::Camera* camera, f32 dt)
{
	Craft::v3 P = camera->GetPosition();
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
	camera->SetPosition(P);
}

void Sample2DLayer::UpdatePlayer(f32 dt) 
{
}

void Sample2DLayer::OnEvent(Craft::Event& event)
{
	Craft::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Sample2DLayer::OnKeyDown));
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Sample2DLayer::OnResizeWindow));
	dispatcher.Dispatch<Craft::MouseScrollWheelEvent>(BIND_EVENT_FN(Sample2DLayer::OnMouseWheelScroll));
}

bool Sample2DLayer::OnKeyDown(Craft::KeyPressedEvent& event)
{
	if (event.GetKeyCode() == VK_ESCAPE)
	{
		exit(1);
	}
	
	if (event.GetKeyCode() == 'F') 
	{
		m_Camera->SetPosition(Craft::v3(0.0, 0.0f, 1.0f));
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
	s += 0.1f * offset;
	m_Camera->SetScale(s);

	return true;
}