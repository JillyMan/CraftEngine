#pragma once

#include <Craft/Graphics/Core/Texture.h>

class Terrain {

private:
	u64 m_Color;
	f32 m_MovementCost;
	bool m_IsWater;

public:
	Terrain(f32 movementCost, bool isWater, u64 color);

	f32 GetMovementCost() const { return m_MovementCost; }
	bool IsWater() const { return m_IsWater; }

	const u64 GetColor() const { return m_Color; }

};