#pragma once

#include "TriangleMesh.h"

namespace Craft { namespace Graphics {

	class Torus : public TriangleMesh {
	public:
		Torus(f32 outerRadius, f32 innterRadius, u32 nSides, u32 nRings);
	};

} }