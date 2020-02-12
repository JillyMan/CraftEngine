#pragma once
#include "Terrain.h"


const Craft::v4 TERRAIN_HILL = Craft::v4(1.0f, 0.0f, 0.0f, 1.0f);
const Craft::v4	TERRAIN_GRASS = Craft::v4(0.0f, 1.0f, 0.0f, 1.0f);
const Craft::v4 TERRAIN_RIVER = Craft::v4(0.0f, 0.0f, 1.0f, 1.0f);

#define WIDTH 15*2
#define HEIGHT 13

class World {
private:
	Terrain* m_Tiles[WIDTH*HEIGHT];

	Terrain grassTerrain_;
	Terrain hillTerrain_;
	Terrain riverTerrain_;

public:
	World();
	~World();

	const u32 GetWidth() const { return WIDTH; }
	const u32 GetHeight() const { return HEIGHT; }

	const Terrain& GetTile(u32 x, u32 y) { return *m_Tiles[x + y * WIDTH]; }
};