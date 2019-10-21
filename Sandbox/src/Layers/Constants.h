#pragma once

#define FOV				45.0f
#define ASPECT_RATIO	DEFAULT_WINDOW_WIDTH / DEFAULT_WINDOW_HEIGHT
#define NEAR_PLANE		0.1f
#define FAR_PLANE		100.0f

std::string RootSpritesFolder = "C:\\Users\\Artsiom\\Documents\\Projects\\CraftEngine\\Assets\\Sprites\\";
std::string PathToGrassImage = "grass.bmp";
std::string PathToSmileImage = "smile.bmp";
std::string PathToTileSheets = "lgbt.bmp";

enum class RotationKind
{
	X,
	Y,
	Z
};