#include "crpch.h"

#include "Game.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/RenderCommand.h>

#include <imgui.h>

using namespace Craft;

Game::Game(Craft::v2 dimension) :
	m_Cube(0.5f),
	m_LightMesh(0.2f),
	m_Torus(0.7f, 0.3f, 30.0f, 30.0f),
	m_Dimension(dimension),
	m_Vfs("C:\\Users\\Artsiom\\Documents\\Projects\\CraftEngine\\Sandbox\\src\\Shaders\\")
{
	Craft::Graphics::RenderCommand::ZTest(true);
	m_CameraController = new OrthoCameraController(dimension.x / dimension.y);

	SetLights();
	SetMatrices(dimension);
}

void Game::SetMatrices(v2 dim) {
	model = mat4::Translate(v3(0.0f, 0.0, -0.5f));
	projection = (mat4::Perspective(70.0f, dim.x / dim.y, 0.3f, 100.0f));
	view = (mat4::LookAt(v3(0.0f, 0.0f, 2.0f), v3(0.0f, 0.0f, 0.0f), v3(0.0f, 1.0f, 0.0f)));
	model *= mat4::Rotate(-35.0f, v3(1.0f, 0.0f, 0.0f));
	model *= mat4::Rotate(35.0f, v3(0.0f, 1.0f, 0.0f));
}

void Game::SetLights() {
	m_LightTransform.Pos = v3(1.0f, 0.0f, 0.0f);
	m_LightSource.Ambient = 0.5f;
	m_LightSource.Color = v3(1.0f, 0.5f, 1.0f);

	m_LightShader = new Craft::Graphics::OpenGLShader();
	m_LightShader->AttachShader(m_Vfs.LoadFileString(String("colored.vert")).c_str(), Craft::Graphics::ShaderType::Vertex);
	m_LightShader->AttachShader(m_Vfs.LoadFileString(String("colored.frag")).c_str(), Craft::Graphics::ShaderType::Fragment);
	m_LightShader->Link();
	m_LightShader->Use();
	m_LightShader->SetUniform3f("Color", m_LightSource.Color);
	m_LightShader->Unuse();

	m_Shader = new Craft::Graphics::OpenGLShader();
	m_Shader->AttachShader(m_Vfs.LoadFileString(String("diffuse.vert")).c_str(), Craft::Graphics::ShaderType::Vertex);
	m_Shader->AttachShader(m_Vfs.LoadFileString(String("diffuse.frag")).c_str(), Craft::Graphics::ShaderType::Fragment);
	m_Shader->Link();
	m_Shader->Use();
	//m_Shader->SetUniform3f("Kd", v3(1.0f, 1.0f, 1.0f));
	//m_Shader->SetUniform3f("LightColor", m_LightSource.Color);
	//m_Shader->SetUniform3f("LightPosition", m_LightTransform.Pos);
	m_Shader->Unuse();
}

Game::~Game() {

}

void Game::OnUpdate(f32 deltaTime) {
	m_CameraController->OnUpdate(deltaTime);

	f32 speed = 5.0f;

	if (Input::InputHandler::IsKeyPressed(VK_UP)) {
		m_LightTransform.Pos.y += speed * deltaTime;
	}
	else if (Input::InputHandler::IsKeyPressed(VK_DOWN)) {
		m_LightTransform.Pos.y -= speed * deltaTime;
	}

	if (Input::InputHandler::IsKeyPressed(VK_LEFT)) {
		m_LightTransform.Pos.x -= speed * deltaTime;
	}
	else if (Input::InputHandler::IsKeyPressed(VK_RIGHT)) {
		m_LightTransform.Pos.x += speed * deltaTime;
	}

	if (Input::InputHandler::IsKeyPressed(VK_HOME)) {
		m_LightTransform.Pos.z += speed * deltaTime;
	}
	else if (Input::InputHandler::IsKeyPressed(VK_END)) {
		m_LightTransform.Pos.z -= speed * deltaTime;
	}
}

void Game::OnRender() {
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 0.0f, 0.0f, 1.0f));
	Craft::Graphics::RenderCommand::Clear();

	m_LightShader->Use();

	m_LightShader->SetUniformMatrix4fv("ModelMatrix", m_LightTransform.ToModelMatrix());
	m_LightShader->SetUniformMatrix4fv("ViewMatrix", m_CameraController->GetCamera()->GetViewMatrix());
	m_LightShader->SetUniformMatrix4fv("ProjectionMatrix", m_CameraController->GetCamera()->GetProjectionMatrix());
	m_LightMesh.Render();


	m_Shader->Use();
	m_Shader->SetUniformMatrix4fv("ModelMatrix", model);
	m_Shader->SetUniformMatrix4fv("ViewMatrix", m_CameraController->GetCamera()->GetViewMatrix());
	m_Shader->SetUniformMatrix4fv("ProjectionMatrix", m_CameraController->GetCamera()->GetProjectionMatrix());

	m_Shader->SetUniform3f("LightColor", m_LightSource.Color);
	m_Shader->SetUniform3f("LightPosition", m_LightTransform.Pos);
	m_Shader->SetUniform1f("AmbientStrength", m_LightSource.Ambient);
	m_Shader->SetUniform3f("ObjectColor", v3(1.0f, 1.0f, 0.0f));
	m_Cube.Render();
	m_Torus.Render();

	m_Shader->SetUniform3f("ObjectColor", v3(0.0f, 1.0f, 0.0f));
	m_Shader->SetUniformMatrix4fv("ModelMatrix", mat4::Translate(v3(-3.0f, 0.0f, 0.0f)) * model);
	m_Cube.Render();
	m_Torus.Render();
}

void Game::OnDebugRender() {
	ImGui::Begin("Game settings");
	ImGui::SliderFloat("Ambient", &m_LightSource.Ambient, 0.0f, 1.0f);
	ImGui::SliderFloat("RotateSpeed", &RotateSpeed, 0.0f, 20.0f);
	ImGui::ColorEdit3("Light", m_LightSource.Color.e);
	ImGui::End();
}

void Game::OnEvent(Craft::Event& event) {
	m_CameraController->OnEvent(event);

	Craft::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Game::OnResizeWindow));
	dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Game::OnKeyoardButtonPressed));
	dispatcher.Dispatch<Craft::MouseButtonPressedEvent>(BIND_EVENT_FN(Game::OnMouseButtonPressed));
	dispatcher.Dispatch<Craft::MouseButtonReleasedEvent>(BIND_EVENT_FN(Game::OnMouseButtonReleased));
	dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(Game::OnMouseMove));
}

bool Game::OnMouseMove(Craft::MouseMovedEvent& event) {
	v2 newPos(event.x, event.y);

	if (m_IsRotating) {
		v2 n = m_StartRotatePos - newPos;
		if (n.x > 0) {
			model *= mat4::Rotate(-RotateSpeed, v3(1.0f, 0.0f, 0.0f));
		}
		else if (n.x < 0) {
			model *= mat4::Rotate(RotateSpeed, v3(1.0f, 0.0f, 0.0f));
		}

		if (n.y > 0) {
			model *= mat4::Rotate(-RotateSpeed, v3(0.0f, 1.0f, 0.0f));
		}
		else if (n.y < 0) {
			model *= mat4::Rotate(RotateSpeed, v3(0.0f, 1.0f, 0.0f));
		}

		m_StartRotatePos = newPos;
		return true;
	}

	return false;
}

bool Game::OnMouseButtonPressed(Craft::MouseButtonPressedEvent& event) {
	if (VK_LBUTTON == event.GetMouseButton()) {
		m_IsRotating = true;
		m_StartRotatePos = v2(event.x, event.y);
		return true;
	}

	return false;
}

bool Game::OnKeyoardButtonPressed(Craft::KeyPressedEvent& event) {
	return false;
}

bool Game::OnMouseButtonReleased(Craft::MouseButtonReleasedEvent& event) {
	m_IsRotating = !(VK_LBUTTON == event.GetMouseButton());
	return m_IsRotating;
}

bool Game::OnResizeWindow(Craft::WindowResizeEvent& event) {
	Craft::Graphics::RenderCommand::SetViewPort(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}