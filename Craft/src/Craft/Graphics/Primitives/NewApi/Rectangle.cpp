#include "crpch.h"
#include "Rectangle.h"

namespace Craft { namespace Graphics {
	
	Rectangle::Rectangle(v2 size) {

		f32 w = size.x / 2.0f;
		f32 h = size.y / 2.0f;

		std::vector<f32> points = {
			 w,  h, 1.0f, // Top Right
			 w, -h, 1.0f, // Bottom Right
			-w, -h, 1.0f, // Bottom Left
			-w,  h, 1.0f, // Top Left 
		};

		std::vector<u32> indices = {
			0, 1, 3,
			1, 2, 3
		};

		std::vector<f32> texCoord = {
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};

		TriangleMesh::InitBuffers (
			&indices,
			&points,
			nullptr,
			&texCoord
		);
	}

} }
