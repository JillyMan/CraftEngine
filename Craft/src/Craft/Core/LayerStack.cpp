#include "crpch.h"
#include "LayerStack.h"

Craft::LayerStack::LayerStack() : 
	m_TopOfLayers(0)
{
}

Craft::LayerStack::~LayerStack()
{
	for (Layer* layer : m_Layers) {
		layer->OnDetach();
		delete layer;
	}
}

void Craft::LayerStack::PushLayer(Layer* layer)
{
	m_Layers.emplace(m_Layers.begin() + m_TopOfLayers, layer);
	m_TopOfLayers++;
	layer->OnAttach();
}

void Craft::LayerStack::PushOverlay(Layer* overlay)
{
	m_Layers.emplace_back(overlay);
	overlay->OnAttach();
}

void Craft::LayerStack::PopLayer(Layer* layer)
{
	auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_TopOfLayers, layer);
	if (it != m_Layers.end()) 
	{
		layer->OnDetach();
		m_Layers.erase(it);
		m_TopOfLayers--;
	}
}

void Craft::LayerStack::PopOverlay(Layer* overlay)
{
	auto it = std::find(m_Layers.begin() + m_TopOfLayers, m_Layers.end(), overlay);
	if (it != m_Layers.end()) 
	{
		overlay->OnDetach();
		m_Layers.erase(it);
	}
}
