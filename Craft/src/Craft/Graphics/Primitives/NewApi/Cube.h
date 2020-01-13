#pragma once

#include "TriangleMesh.h"

namespace Craft { namespace Graphics {

	class Cube : public TriangleMesh {

	public:
		Cube(f32 side);
		virtual ~Cube() {}
	};

} }