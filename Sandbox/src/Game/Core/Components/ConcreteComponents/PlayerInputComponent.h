#pragma once

#include "../Abstractions/InputComponent.h"

class PlayerInputComponent : public InputComponent {
private:
	f32 m_Speed;

public:
	PlayerInputComponent(f32 speed) : 
		m_Speed(speed) { }

	virtual void Update(GameObject& obj, f32 dt) override {
		if (Craft::Input::InputHandler::IsKeyPressed('W')) {
			obj.Transform.Pos.y -= m_Speed * dt;
		}
		else if (Craft::Input::InputHandler::IsKeyPressed('S')) {
			obj.Transform.Pos.y += m_Speed * dt;
		}
		if (Craft::Input::InputHandler::IsKeyPressed('A')) {
			obj.Transform.Pos.x -= m_Speed * dt;
		}
		else if (Craft::Input::InputHandler::IsKeyPressed('D')) {
			obj.Transform.Pos.y += m_Speed * dt;
		}
	}
};