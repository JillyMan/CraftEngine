#include "crpch.h"

#include "Scene3D.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include <Craft/Graphics/Renderer.h>
#include <Craft/Graphics/RenderCommand.h>

Scene3D::Scene3D(Craft::v2 dimension) : m_Dimension(dimension) {
	using namespace Craft;

	v3 cameraPos = v3(0.0f, 0.0f, -5.0f);
	v3 cameraFront = v3(0.0f, 0.0f, -1.0f);
	v3 cameraUp = v3(0.0f, 1.0f, 0.0f);

	v2 lasMousePos = v2(m_Dimension.x/ 2, m_Dimension.y / 2);
	m_Camera = new FPSCameraController(5.0f,
		cameraPos, cameraFront, cameraUp, lasMousePos,
		mat4::Perspective(75.0f, m_Dimension.x / m_Dimension.y, 0.1f, 100.0f));

	m_Cube = new Craft::Graphics::Cube(1.0f);
	m_Rect = new Craft::Graphics::Rectangle(Craft::v2(1.0f));

	const char* vertexShader = R"(
#version 460 core
layout (location = 0) in vec3 pos;

uniform mat4 u_Model = mat4(1.0f);
uniform mat4 u_Proj = mat4(1.0f);
uniform mat4 rot = mat4(1.0f);

uniform vec3 u_Color;

out vec4 o_Color;

void main() {
	gl_Position = rot * vec4(pos, 1.0f);
	o_Color = vec4(u_Color, 1.0f);
}
)";

	const char* fragmentShader = R"(
#version 460 core

in vec4 o_Color;
out vec4 color;

void main() {
	color = o_Color;
}
)";

	m_Shader = new Craft::Graphics::OpenGLShader(vertexShader, fragmentShader);
}

Scene3D::~Scene3D() {

}

void Scene3D::OnEvent(Craft::Event& event) {
	Craft::EventDispatcher dispatcher(event);
	dispatcher.Dispatch<Craft::WindowResizeEvent>(BIND_EVENT_FN(Scene3D::OnResizeWindow));
}

float rotate;
void Scene3D::OnUpdate(f32 deltaTime) {
	rotate += sinf(deltaTime);
}

void Scene3D::OnRender() {
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 1.0f, 0.0f, 1.0f));
	Craft::Graphics::RenderCommand::Clear();

	m_Shader->Use();
	m_Shader->SetUniform3f("u_Color", Craft::v3(1.0f, 0.5f, 0.0f));
	m_Shader->SetUniformMatrix4fv("rot", Craft::mat4::Rotate(rotate, Craft::v3(0.0f, 0.0f, 1.0f)));
	//m_Cube->Render();
	m_Rect->Render();
}

void Scene3D::OnDebugRender() {

}

bool Scene3D::OnResizeWindow(Craft::WindowResizeEvent& event) {
	Craft::Graphics::RenderCommand::SetViewPort(0, 0, event.GetWidth(), event.GetHeight());
	return true;
}

