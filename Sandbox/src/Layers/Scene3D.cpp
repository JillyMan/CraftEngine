#include "crpch.h"

#include "Scene3D.h"
#include <Platform/OpenGL/OpenGLShader.h>
#include <Craft/Graphics/Renderer.h>

Scene3D::Scene3D(Craft::v2 dimension) : m_Dimension(dimension) {
	using namespace Craft;

	v3 cameraPos = v3(0.0f, 0.0f, -5.0f);
	v3 cameraFront = v3(0.0f, 0.0f, -1.0f);
	v3 cameraUp = v3(0.0f, 1.0f, 0.0f);

	v2 lasMousePos = v2(m_Dimension.x/ 2, m_Dimension.y / 2);
	m_Camera = new FPSCameraController(5.0f,
		cameraPos, cameraFront, cameraUp, lasMousePos,
		mat4::Perspective(75.0f, m_Dimension.x/ m_Dimension.y, 0.1f, 100.0f));

	m_Cube = new Craft::Graphics::Cubee(1);

	const char* vertexShader = R"(
#version 460 core
layout (location = 0) in vec3 pos;

uniform mat4 model;
uniform mat4 proj;

out v4 color;

void main() {
	gl_Position = vec4(pos, 1.0f);
	color = v4(1.0f, 0.0f, 0.0f, 1.0f);
}
)";

	const char* fragmentShader = R"(
#version 460 core
in vec4 inColor;

void main() {
	color = inColor;
}

)";

	m_Shader = new Craft::Graphics::OpenGLShader(vertexShader, "");
}

Scene3D::~Scene3D() {

}

void Scene3D::OnEvent(Craft::Event& event) {

}

void Scene3D::OnUpdate(f32 deltaTime) {

}
void Scene3D::OnRender() {
	//Craft::Graphics::Renderer::BeginScene(*m_Camera);
	//Craft::mat4 modelMatrix = Craft::mat4::Translate(m_CubePos);

	m_Cube->Render();
}

void Scene3D::OnDebugRender() {

}
