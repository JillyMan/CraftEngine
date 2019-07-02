#pragma once

namespace Craft
{
	struct v4
	{
		union
		{
			struct
			{
				f32 x, y, z, w;
			};
			struct
			{
				f32 r, g, b, a;
			};

			f32 e[4];
		};

		v4()
		{
			memchr(e, 0, 4);
		}

		v4(v4& v) :
			v4(v.x, v.y, v.z, v.w)
		{
		}

		v4(f32 x, f32 y, f32 z, f32 w) : 
			x(x), y(y), z(z), w(w)
		{
		}
	};

	struct v3
	{
		union
		{
			struct
			{
				f32 x, y, z;
			};

			struct
			{
				f32 r, g, b;
			};

			f32 e[3];
		};

		v3()
		{
			memchr(e, 0, 3);
		}

		v3(v3& v) :
			v3(v.x, v.y, v.z)
		{
		}

		v3(f32 x, f32 y, f32 z) :
			x(x), y(y), z(z)
		{
		}
	};

	struct v2
	{
		union
		{
			struct
			{
				f32 x, y;
			};
			f32 e[2];
		};

		v2()
		{
			memchr(e, 0, 2);
		}

		v2(v2& v) :
			v2(v.x, v.y)
		{
		}

		v2(f32 x, f32 y) :
			x(x), y(y)
		{
		}
	};

	v4 operator + (v4& a, v4&b);
	v4 operator - (v4& a, v4&b);
	v4 operator * (v4& a, v4&b);
	v4 operator / (v4& a, v4&b);

	void operator *= (v4& a, const v4&b);
	void operator /= (v4& a, const v4&b);
	void operator -= (v4& a, const v4&b);
	void operator += (v4& a, const v4&b);
	
	std::ostream& operator << (std::ostream& os, v4& v);
}