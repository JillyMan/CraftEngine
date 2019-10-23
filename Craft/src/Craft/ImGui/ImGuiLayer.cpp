#include "crpch.h"

#include "imgui.h"

#include "ImGuiLayer.h"

#include "Platform/OpenGL/ImGuiImplOpenGL3.h"
#include "Platform/Windows/ImGuiImplWin32.h"


Craft::ImGuiLayer::ImGuiLayer()
{
	const char* version = "#version 430 core";
	ImGui_ImplOpenGL3_Init(version);
}

Craft::ImGuiLayer::~ImGuiLayer()
{
}

void Craft::ImGuiLayer::OnAttach()
{
}

void Craft::ImGuiLayer::OnDetach()
{
}

void Craft::ImGuiLayer::OnEvent(Event& event)
{
}

void Craft::ImGuiLayer::OnUpdate(f32 deltaTime)
{
}

void Craft::ImGuiLayer::OnRender()
{
}
