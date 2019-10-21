#include "crpch.h"

#include "Sample2DLayer.h"
#include <Craft/Graphics/RenderCommand.h>

Sample2DLayer::Sample2DLayer() 
{
	Craft::Graphics::RenderCommand::SetClearColor(Craft::v4(0.0f, 0.1f, 0.1f, 1.0f));
	m_Camera = Craft::Camera::CreateOrthographicCamera(
		-16.0f, 16.0f, -9.0f, -9.0f, 0.1f, 1000.0f);
}

Sample2DLayer::~Sample2DLayer()
{

}

void Sample2DLayer::OnEvent(Craft::Event& event) 
{

}

void Sample2DLayer::OnRender() 
{

}

void Sample2DLayer::OnUpdate(f32 dt)
{
	Craft::Graphics::RenderCommand::Clear();
}