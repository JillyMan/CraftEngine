#include "crpch.h"

#include "Terrain.h"

Terrain::Terrain(f32 movementCost, bool isWater, u64 color) :
	m_Color(color),
	m_IsWater(isWater),
	m_MovementCost(movementCost)
{
}