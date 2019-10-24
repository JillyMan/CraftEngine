#include "crpch.h"

#include "ImGuiLayer.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiImplOpenGL3.h"
#include "Platform/Windows/ImGuiImplWin32.h"

#include "Craft/Core/Application.h"

Craft::ImGuiLayer::ImGuiLayer()
{
}

Craft::ImGuiLayer::~ImGuiLayer()
{
}

void Craft::ImGuiLayer::OnAttach()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	ImGui::StyleColorsDark();

	Application& app = Application::Get();
	ImGui_ImplWin32_Init(app.GetWindow().GetWindowHandle());
	ImGui_ImplOpenGL3_Init("#version 410");
}

void Craft::ImGuiLayer::OnDetach()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplWin32_Shutdown();
	ImGui::DestroyContext();
}

void Craft::ImGuiLayer::Begin()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
}

void Craft::ImGuiLayer::End()
{
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();

	Window& window = Application::Get().GetWindow();
	io.DisplaySize = ImVec2((f32)window.GetWidth(), (f32)window.GetHeight());
}

void Craft::ImGuiLayer::OnDebugRender()
{
	//static bool show = true;
	//ImGui::ShowDemoWindow(&show);
}
