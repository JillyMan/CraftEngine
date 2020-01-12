#pragma once

#include "TriangleMesh.h"

namespace Craft { namespace Graphics {

	class Cubee : public TriangleMesh {

	public:
		Cubee(f32 side);
		virtual ~Cubee();
	};

} }