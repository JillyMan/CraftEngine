#pragma once

#include <xmmintrin.h>

namespace Craft
{

	union v4
	{
		struct 
		{
			f32 x, y, w, z;
		};
		f32 e[4];
	};

	v4 operator + (v4& a, v4& b)
	{
		__m128* a_simd = (__m128*)a.e;
		__m128* b_simd = (__m128*)b.e;

		v4* res = (v4*)_aligned_malloc(4 * sizeof(float), 32);
		_mm_store_ps(res->e, _mm_add_ps(*a_simd, *b_simd));

		return *res;
	}

}