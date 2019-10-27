#include "crpch.h"
#include "Sample2DLayer.h"

#include <Craft/Core/Application.h>
#include <Craft/Graphics/RenderCommand.h>
#include <Craft/Core/InputHandler.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/Primitives/Sprite.h>

#include <imgui.h>

Sample2DLayer::Sample2DLayer() :
	m_Camera(16.0f / 9.0f)
{
	GraphicsInit();
	PlayerInit();
	Physic::Init();
}

void Sample2DLayer::GraphicsInit() {
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 0.1f, 0.1f, 1.0f));

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

void Sample2DLayer::PlayerInit() 
{
	Physic::AABB aabb;
	aabb.min = v2(0.0f, 0.0f);
	aabb.max = v2(1.0f, 1.0f);
	m_Player = Physic::CreateRigidBody(1.0f, 1.0f, v2(0.0f, 0.0f) - m_Origin, aabb);
	Physic::AddRigidBody(m_Player);
	m_Speed = 12.5f;

	Physic::AABB aabbBlock;
	aabbBlock.min = v2(0.0f, 0.0f);
	aabbBlock.max = v2(1.0f, 1.0f);
	m_Block = Physic::CreateRigidBody(1.0f, 100.0f, v2(-0.5f, -0.5f) - m_Origin, aabbBlock);

	Physic::AddRigidBody(m_Block);
	//Physic::AddGlobalForce(v2( 0.0f, -0.00098f)); // gravity
}

Sample2DLayer::~Sample2DLayer()
{
}

void Sample2DLayer::OnDebugRender()
{
	ImGui::Begin("2D game settings");
	ImGui::SliderFloat("Speed", &m_Speed, 0.0f, 100.0f);
	ImGui::Text("Player.X: %f", m_Player->pos.x);
	ImGui::Text("Player.Y: %f", m_Player->pos.y);

	ImGui::SliderFloat("Scale", &m_ScaleRatio, 0.0f, 3.0f);
	ImGui::ColorPicker3("Tiles color", m_Color.e);
	ImGui::End();
}

void Sample2DLayer::OnRender()
{
	Craft::Graphics::RenderCommand::Clear();
	Craft::Graphics::Renderer::BeginScene(m_Camera.GetCamera());

	m_Shader->Use();
	m_Shader->SetUniform3f("u_color", m_Color);

	Craft::mat4 scaleMat = Craft::mat4::Scale(Craft::v3(m_ScaleRatio));
	Craft::mat4 transofrm = Craft::mat4::Translate(v3(m_Player->pos, 0.0f)) * scaleMat;
	Craft::Graphics::Renderer::Submit(m_VertexArray, m_Shader, transofrm);

	m_Shader->SetUniform3f("u_color", v3(1.0f, 0.0f, 0.0f));
	scaleMat = Craft::mat4::Scale(Craft::v3(m_ScaleRatio));
	transofrm = Craft::mat4::Translate(v3(m_Block->pos, 0.0f)) * scaleMat;
	Craft::Graphics::Renderer::Submit(m_VertexArray, m_Shader, transofrm);
}

void Sample2DLayer::OnUpdate(f32 dt)
{
	m_Camera.Update(dt);
	UpdatePlayer(dt);

	Physic::UpdatePhysics(dt);
}

void Sample2DLayer::UpdatePlayer(f32 dt) 
{
	v2 force;
	
	if (Craft::Input::InputHandler::IsKeyPressed(VK_UP))
	{
		force.y = 1.0f;
	}
	else if (Craft::Input::InputHandler::IsKeyPressed(VK_DOWN))
	{
		force.y = -1.0f;
	}

	if (Craft::Input::InputHandler::IsKeyPressed(VK_RIGHT))
	{
		force.x = 1.0f;
	}
	else if (Craft::Input::InputHandler::IsKeyPressed(VK_LEFT))
	{
		force.x = -1.0f;
	}

	force *= m_Speed;

	ApplyForce(*m_Player, force, dt/100.0f);
}

void Sample2DLayer::OnEvent(Craft::Event& e)
{
	m_Camera.OnEvent(e);

	Craft::EventDispatcher dispatcher(e);
	dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Sample2DLayer::OnKeyDown));
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Sample2DLayer::OnResizeWindow));
}

bool Sample2DLayer::OnKeyDown(Craft::KeyPressedEvent& event)
{
	if (event.GetKeyCode() == VK_ESCAPE)
	{
		exit(1);
	}
	
	if (event.GetKeyCode() == 'F') 
	{
//		m_Camera.SetPosition(Craft::v3(0.0, 0.0f, 1.0f));
	}
	return false;
}

bool Sample2DLayer::OnResizeWindow(Craft::WindowResizeEvent& event) {
	//todo: move to renderer static method!!
	glViewport(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}
