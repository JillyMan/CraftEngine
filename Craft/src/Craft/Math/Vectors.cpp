#include "crpch.h"
#include "Vectors.h"
#include "MathUtils.h"

namespace Craft
{
	//-------------
	//v2 operations
	//-------------
	v2 operator + (v2& a, v2&b)
	{
		v2 c;
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		return c;
	}

	v2 operator - (v2& a, v2& b)
	{
		v2 c;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		return c;
	}

	v2 operator * (v2& a, v2& b)
	{
		v2 c;
		c.x = a.x * b.x;
		c.y = a.y * b.y;
		return c;
	}

	v2 operator / (v2& a, v2& b)
	{
		v2 c;
		c.x = a.x / b.x;
		c.y = a.y / b.y;
		return c;
	}

	v2 operator *= (v2& a, v2& b)
	{
		a = a * b;
		return a;
	}

	v2 operator /= (v2& a, v2& b)
	{
		a = a / b;
		return a;
	}

	v2 operator -= (v2& a, v2& b)
	{
		a = a - b;
		return a;
	}

	v2 operator += (v2& a, v2& b)
	{
		a = a + b;
		return a;
	}


	v2 operator + (v2& a, f32 value)
	{
		v2 c;
		c.x = a.x + value;
		c.y = a.y + value;
		return c;
	}

	v2 operator - (v2& a, f32 value)
	{
		v2 c;
		c.x = a.x - value;
		c.y = a.y - value;
		return c;
	}

	v2 operator - (v2& a)
	{
		v2 c;
		c.x = -a.x;
		c.y = -a.y;
		return c;
	}


	v2 operator * (v2& a, f32 value)
	{
		v2 c;
		c.x = a.x * value;
		c.y = a.y * value;
		return c;
	}

	v2 operator / (v2& a, f32 value)
	{
		v2 c;
		c.x = a.x / value;
		c.y = a.y / value;
		return c;
	}

	v2 operator *= (v2& a, f32 value)
	{
		a = a * value;
		return a;
	}

	v2 operator /= (v2& a, f32 value)
	{
		a = a / value;
		return a;
	}

	v2 operator -= (v2& a, f32 value)
	{
		a = a - value;
		return a;
	}

	v2 operator += (v2& a, f32 value)
	{
		a = a + value;
		return a;
	}

	v2 Normalize(v2& a)
	{
		f32 len = Length(a);
		return a / len;
	}

	v2 Lerp(Craft::v2& start, Craft::v2& end, f32 t)
	{
		return v2 (
			Lerp(start.x, end.x, t),
			Lerp(start.y, end.y, t)
		);
	}

	f32 Length(v2& a)
	{
		f32 result = sqrt(a.x * a.x + a.y * a.y);
		return result;
	}

	f32 Dot(v2& a, v2& b)
	{
		f32 result = a.x * b.x + a.y * b.y;
		return result;
	}

//-------------
//v3 operations
//-------------
	v3 operator + (v3& a, v3& b)
	{
		v3 c;
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
		return c;
	}

	v3 operator - (v3& a, v3& b)
	{
		v3 c;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
		return c;
	}

	v3 operator * (v3& a, v3& b)
	{
		v3 c;
		c.x = a.x * b.x;
		c.y = a.y * b.y;
		c.z = a.z * b.z;
		return c;
	}

	v3 operator / (v3& a, v3& b)
	{
		v3 c;
		c.x = a.x / b.x;
		c.y = a.y / b.y;
		c.z = a.z / b.z;
		return c;
	}

	v3 operator *= (v3& a, v3& b)
	{
		a = a * b;
		return a;
	}

	v3 operator /= (v3& a, v3& b)
	{
		a = a / b;
		return a;
	}

	v3 operator -= (v3& a, v3& b)
	{
		a = a - b;
		return a;
	}

	v3 operator += (v3& a, v3& b)
	{
		a = a + b;
		return a;
	}

	v3 operator + (v3& a, f32 value)
	{
		v3 c;
		c.x = a.x + value;
		c.y = a.y + value;
		c.z = a.z + value;
		return c;
	}

	v3 operator - (v3& a, f32 value)
	{
		v3 c;
		c.x = a.x - value;
		c.y = a.y - value;
		c.z = a.z - value;
		return c;
	}

	v3 operator - (v3& a)
	{
		v3 c;
		c.x = -a.x;
		c.y = -a.y;
		c.z = -a.z;
		return c;
	}


	v3 operator * (v3& a, f32 value)
	{
		v3 c;
		c.x = a.x * value;
		c.y = a.y * value;
		c.z = a.z * value;
		return c;
	}

	v3 operator / (v3& a, f32 value)
	{
		v3 c;
		c.x = a.x / value;
		c.y = a.y / value;
		c.z = a.z / value;
		return c;
	}

	v3 operator *= (v3& a, f32 value)
	{
		a = a * value;
		return a;
	}

	v3 operator /= (v3& a, f32 value)
	{
		a = a / value;
		return a;
	}

	v3 operator -= (v3& a, f32 value)
	{
		a = a - value;
		return a;
	}

	v3 operator += (v3& a, f32 value)
	{
		a = a + value;
		return a;
	}

	f32 Length(v3& a)
	{
		f32 result = a.x * a.x + a.y * a.y + a.z * a.z;
		result = sqrt(result);
		return result;
	}

	f32 Dot(v3& a, v3& b)
	{
		f32 result = a.x * a.x + a.y * a.y + a.z * a.z;
		return result;
	}

	v3 Cross(v3& a, v3& b)
	{
		v3 �;
		�.x = a.y * b.z - a.z * b.y;
		�.y = a.z * b.x - a.x * b.z;
		�.z = a.x * b.y - a.y * b.x;
		return �;
	}

	v3 Normalize(v3& a)
	{
		f32 len = Length(a);
		return a / len;
	}

	//-------------
	//v4 operations
	//-------------
	v4 operator + (v4& a, v4& b)
	{
		v4 c;
		c.x = a.x + b.x;
		c.y = a.y + b.y;
		c.z = a.z + b.z;
		c.w = a.w + b.w;
		return c;
	}

	v4 operator - (v4& a, v4& b)
	{
		v4 c;
		c.x = a.x - b.x;
		c.y = a.y - b.y;
		c.z = a.z - b.z;
		c.w = a.w - b.w;
		return c;
	}

	v4 operator * (v4& a, v4& b)
	{
		v4 c;
		c.x = a.x * b.x;
		c.y = a.y * b.y;
		c.z = a.z * b.z;
		c.w = a.w * b.w;
		return c;
	}

	v4 operator / (v4& a, v4& b)
	{
		v4 c;
		c.x = a.x / b.x;
		c.y = a.y / b.y;
		c.z = a.z / b.z;
		c.w = a.w / b.w;
		return c;
	}

	v4 operator *= (v4& a, v4& b)
	{
		a = a * b;
		return a;
	}

	v4 operator /= (v4& a, v4& b)
	{
		a = a / b;
		return a;
	}

	v4 operator -= (v4& a, v4& b)
	{
		a = a - b;
		return a;
	}

	v4 operator += (v4& a, v4& b)
	{
		a = a + b;
		return a;
	}

	f32 Length(v4& a)
	{
		f32 result = 0.0f;
		for (int i = 0; i < 4; ++i)
		{
			result += a.e[i] * a.e[i];
		}
		result = sqrt(result);
		return result;
	}

	f32 Dot(v4& a, v4& b)
	{
		f32 result = 0.0f;
		for (int i = 0; i < 4; ++i)
		{
			result += (a.e[i] * b.e[i]);
		}
		return result;
	}

	//----debug feachers-----
	std::ostream& operator << (std::ostream& os, v2& v)
	{
		return (os << "{ " << v.x << " " << v.y << " }" << std::endl);
	}

	std::ostream& operator << (std::ostream& os, v3& v)
	{
		return (os << "{ " << v.x << " "
			<< v.y << " "
			<< v.z << " }" << std::endl);
	}

	std::ostream& operator << (std::ostream& os, v4& v)
	{
		return (os << "{ " << v.x << " "
			<< v.y << " "
			<< v.z << " "
			<< v.w << " }" << std::endl);
	}
}