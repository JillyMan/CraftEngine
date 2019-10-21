#pragma once

#include <Craft/Layer.h>
#include <Craft/Graphics/Cameras/Camera.h>

class Sample2DLayer : public Craft::Layer
{
private:
	Craft::Camera* m_Camera;

public:
	Sample2DLayer();
	~Sample2DLayer();

	virtual void OnEvent(Craft::Event& e) override;
	virtual void OnUpdate(f32 deltaTime)  override;
	virtual void OnRender() override;
};
