#include "crpch.h"

#include "Scene3D.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/RenderCommand.h>

#include <imgui.h>

using namespace Craft;

Scene3D::Scene3D(Craft::v2 dimension) :
	m_Cube(0.5f),
	m_Dimension(dimension),
	m_Torus(0.7f, 0.3f, 30.0f, 30.0f), 
	m_Vfs("C:\\Users\\Artsiom\\Documents\\Projects\\CraftEngine\\Sandbox\\src\\Shaders\\")
{
	v3 CamPos = v3(0.0f, 0.0f, -2.0f);
	v3 CamFront = v3(0.0f, 0.0f, -1.0f);
	v3 CamUp = v3(0.0f, 1.0f, 0.0f);
	
	v2 lasMousePos = v2(dimension.x / 2, dimension.y / 2);
	m_CameraController = new FPSCameraController(5.0f, CamPos, CamFront, CamUp, lasMousePos);

	SetMatrices(dimension);

	m_Rect = new Craft::Graphics::Rectangle(Craft::v2(1.0f));

	m_Shader = new Craft::Graphics::OpenGLShader();
	m_Shader->AttachShader(m_Vfs.LoadFileString(String("diffuse.vert")).c_str(), Craft::Graphics::ShaderType::Vertex);
	m_Shader->AttachShader(m_Vfs.LoadFileString(String("diffuse.frag")).c_str(), Craft::Graphics::ShaderType::Fragment);
	m_Shader->Link();
	m_Shader->Use();
	m_Shader->SetUniform3f("Kd", v3(1.0f, 1.0f, 1.0f));
	m_Shader->SetUniform3f("Ld", v3(1.0f, 1.0f, 1.0f));
	lightPos = v4(5.0f, 5.0f, 2.0f, 1.0f);
	m_Shader->SetUniform4f("LightPosition", lightPos);
	m_Shader->Unuse();

	Craft::Graphics::RenderCommand::ZTest(true);
}

Scene3D::~Scene3D() {

}

void Scene3D::OnEvent(Craft::Event& event) {
	Craft::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Scene3D::OnResizeWindow));
	dispatcher.Dispatch<Craft::KeyPressedEvent>(BIND_EVENT_FN(Scene3D::OnKeyoardButtonPressed));
	dispatcher.Dispatch<Craft::MouseButtonPressedEvent>(BIND_EVENT_FN(Scene3D::OnMouseButtonPressed));
	dispatcher.Dispatch<Craft::MouseButtonReleasedEvent>(BIND_EVENT_FN(Scene3D::OnMouseButtonReleased));
	dispatcher.Dispatch<Craft::MouseMovedEvent>(BIND_EVENT_FN(Scene3D::OnMouseMove));

}

void Scene3D::OnUpdate(f32 deltaTime) {
	m_CameraController->Update(deltaTime);
}

void Scene3D::OnRender() {
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 0.0f, 0.0f, 1.0f));
	Craft::Graphics::RenderCommand::Clear();

	m_Shader->Use();

	m_Shader->SetUniformMatrix4fv("ModelMatrix", model);
	m_Shader->SetUniformMatrix4fv("ViewMatrix", m_CameraController->GetCamera()->GetViewMatrix());
	m_Shader->SetUniformMatrix4fv("ProjectionMatrix", m_CameraController->GetCamera()->GetProjectionMatrix());

	m_Shader->SetUniform4f("LightPosition", lightPos);
	m_Shader->SetUniform1f("AmbientStrength", AmbientStrength);

	m_Cube.Render();
	m_Torus.Render();
}

void Scene3D::OnDebugRender() {
	ImGui::Begin("2D game settings");
	ImGui::SliderFloat("Ambient", &AmbientStrength, 0.0f, 1.0f);
	ImGui::SliderFloat("RotateSpeed", &RotateSpeed, 0.0f, 20.0f);
	ImGui::End();
}

void Scene3D::SetMatrices(v2 dim) {
	model = (mat4::Identity());
	projection = (mat4::Perspective(70.0f, dim.x / dim.y, 0.3f, 100.0f));
	view = (mat4::LookAt(v3(0.0f, 0.0f, 2.0f), v3(0.0f, 0.0f, 0.0f), v3(0.0f, 1.0f, 0.0f)));
	model *= mat4::Rotate(-35.0f, v3(1.0f, 0.0f, 0.0f));
	model *= mat4::Rotate(35.0f, v3(0.0f, 1.0f, 0.0f));
}

bool Scene3D::OnMouseMove(Craft::MouseMovedEvent& event) {
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

	if (Input::InputHandler::IsKeyPressed('R')) {
		m_CameraController->OnMouseEvent(newPos.x, newPos.y);
	}

	return false;
}

bool Scene3D::OnMouseButtonPressed(Craft::MouseButtonPressedEvent& event) {
	if (VK_LBUTTON == event.GetMouseButton()) {
		m_IsRotating = true;
		m_StartRotatePos = v2(event.x, event.y);
		return true;
	}

	return false;
}

bool Scene3D::OnKeyoardButtonPressed(Craft::KeyPressedEvent& event) {
	if ('R' == event.GetKeyCode()) {
		s32 x, y;
		Input::InputHandler::GetMousePosition(x, y);
		m_CameraController->SetLastPos(x, y);
		return true;
	}

	return false;
}

bool Scene3D::OnMouseButtonReleased(Craft::MouseButtonReleasedEvent& event) {
	m_IsRotating = !(VK_LBUTTON == event.GetMouseButton());
	return m_IsRotating;
}

bool Scene3D::OnResizeWindow(Craft::WindowResizeEvent& event) {
	Craft::Graphics::RenderCommand::SetViewPort(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}

