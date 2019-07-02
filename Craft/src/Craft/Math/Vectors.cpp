#include <crpch.h>

#include "Vectors.h"

namespace Craft 
{
	v4 operator + (v4& a, v4&b)
	{
		v4 c {};
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
		c.w = a.w + b.w;
		return c;
	}

	v4 operator - (v4& a, v4&b)
	{
		v4 c {};
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
		c.w = a.w - b.w;
		return c;
	}

	v4 operator * (v4& a, v4&b)
	{
		v4 c {};
		c.x = a.x * b.x;
		c.y = a.y * b.y;
		c.z = a.z * b.z;
		c.w = a.w * b.w;
		return c;
	}

	v4 operator / (v4& a, v4&b)
	{
		v4 c {};
		c.x = a.x / b.x;
		c.y = a.y / b.y;
		c.z = a.z / b.z;
		c.w = a.w / b.w;
		return c;
	}

	void operator *= (v4& a, const v4&b)
	{
		a.x *= b.x;
		a.y *= b.y;
		a.z *= b.z;
		a.w *= b.w;
	}

	void operator /= (v4& a, const v4&b)
	{
		a.x /= b.x;
		a.y /= b.y;
		a.z /= b.z;
		a.w /= b.w;
	}

	void operator -= (v4& a, const v4&b)
	{
		a.x -= b.x;
		a.y -= b.y;
		a.z -= b.z;
		a.w -= b.w;
	}

	void operator += (v4& a, const v4&b)
	{
		a.x += b.x;
		a.y += b.y;
		a.z += b.z;
		a.w += b.w;
	}

	std::ostream& operator << (std::ostream& os, v4& v)
	{
		return (os << "{ " << v.x << " "
						  << v.y << " "
						  << v.z << " "
						  << v.w << " }" << std::endl);
	}
}