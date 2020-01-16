#pragma once

#include "TriangleMesh.h"
#include <Craft/Math/Vectors.h>

namespace Craft { namespace Graphics {

	class Rectangle : public TriangleMesh {
	public:
		Rectangle(v2 size);
		virtual ~Rectangle() {}
	};

} }