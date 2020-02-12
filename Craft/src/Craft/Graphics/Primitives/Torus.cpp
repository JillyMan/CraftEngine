#include "crpch.h"
#include "Torus.h"
#include <Craft/Math/MathUtils.h>

Craft::Graphics::Torus::Torus(f32 outerRadius, f32 innerRadius, u32 nsides, u32 nrings) {

	u32 faces = nsides * nrings;
	int nVerts = nsides * (nrings + 1);   // One extra ring to duplicate first ring

	// Points
	std::vector<f32> p(3 * nVerts);
	// Normals
	std::vector<f32> n(3 * nVerts);
	// Tex coords
	std::vector<f32> tex(2 * nVerts);
	// Elements
	std::vector<u32> el(6 * faces);

	// Generate the vertex data
	float ringFactor = TWO_PI / nrings;
	float sideFactor = TWO_PI / nsides;
	int idx = 0, tidx = 0;
	for (u32 ring = 0; ring <= nrings; ring++) {
		float u = ring * ringFactor;
		float cu = cos(u);
		float su = sin(u);
		for (u32 side = 0; side < nsides; side++) {
			float v = side * sideFactor;
			float cv = cos(v);
			float sv = sin(v);
			float r = (outerRadius + innerRadius * cv);
			p[idx] = r * cu;
			p[idx + 1] = r * su;
			p[idx + 2] = innerRadius * sv;
			n[idx] = cv * cu * r;
			n[idx + 1] = cv * su * r;
			n[idx + 2] = sv * r;
			tex[tidx] = u / TWO_PI;
			tex[tidx + 1] = v / TWO_PI;
			tidx += 2;
			// Normalize
			float len = sqrt(n[idx] * n[idx] +
				n[idx + 1] * n[idx + 1] +
				n[idx + 2] * n[idx + 2]);
			n[idx] /= len;
			n[idx + 1] /= len;
			n[idx + 2] /= len;
			idx += 3;
		}
	}

	idx = 0;
	for (u32 ring = 0; ring < nrings; ring++) {
		u32 ringStart = ring * nsides;
		u32 nextRingStart = (ring + 1) * nsides;
		for (u32 side = 0; side < nsides; side++) {
			int nextSide = (side + 1) % nsides;
			// The quad
			el[idx] = (ringStart + side);
			el[idx + 1] = (nextRingStart + side);
			el[idx + 2] = (nextRingStart + nextSide);
			el[idx + 3] = ringStart + side;
			el[idx + 4] = nextRingStart + nextSide;
			el[idx + 5] = (ringStart + nextSide);
			idx += 6;
		}
	}

	InitBuffers(&el, &p, &n, &tex);
}
