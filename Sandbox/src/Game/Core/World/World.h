#pragma once

enum TerrainColor {
	TERRAIN_HILL = 0x6B8E23,
	TERRAIN_GRASS = 0x8B4513,
	TERRAIN_RIVER = 0x00BFFF,
	//...
};

#define WIDTH 12
#define HEIGHT 10

#include "Terrain.h"



class World {
private:
	Terrain* m_Tiles[WIDTH][HEIGHT];

	Terrain grassTerrain_;
	Terrain hillTerrain_;
	Terrain riverTerrain_;

public:
	World();
	~World();

	const Terrain& GetTile(u32 x, u32 y) { return *m_Tiles[x][y]; }


};