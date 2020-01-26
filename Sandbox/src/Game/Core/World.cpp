#include "crpch.h"

#include "World.h"

World::World() :
	grassTerrain_(0.5f, false, TerrainColor::TERRAIN_GRASS),
	hillTerrain_(1.0f, false, TerrainColor::TERRAIN_HILL),
	riverTerrain_(0.0f, true, TerrainColor::TERRAIN_RIVER)
{
}

World::~World() {
}