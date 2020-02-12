#pragma once

#include <Craft/Math/Vectors.h>

#include <Craft/Graphics/Core/Texture.h>


class Terrain {

private:
	Craft::v4 m_Color;
	f32 m_MovementCost;
	bool m_IsWater;

public:
	Terrain(f32 movementCost, bool isWater, Craft::v4 color);

	f32 GetMovementCost() const { return m_MovementCost; }
	bool IsWater() const { return m_IsWater; }

	const Craft::v4 GetColor() const { return m_Color; }
};