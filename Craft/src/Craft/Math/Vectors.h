#pragma once

namespace Craft
{
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

		v2() = default;

		v2(f32 x, f32 y) :
			x(x), y(y)
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

			struct
			{
				v2 xy;
				f32 _Ignored3;
			};

			f32 e[3];
		};

		v3() = default;

		v3(f32 x, f32 y, f32 z) :
			x(x), y(y), z(z)
		{
		}
	};

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

			struct
			{
				v2 xy;
				f32 _Ignored3;
				f32 _Ignored4;
			};

			struct
			{
				v3 xyz;
				f32 _Ignored4;
			};

			f32 e[4];
		};

		v4() = default;

		v4(f32 x, f32 y, f32 z, f32 w) :
			x(x), y(y), z(z), w(w)
		{
		}
	};

	v2 operator + (v2& a, v2&b);
	v2 operator - (v2& a, v2&b);
	v2 operator * (v2& a, v2&b);
	v2 operator / (v2& a, v2&b);

	v2 operator *= (v2& a, v2&b);
	v2 operator /= (v2& a, v2&b);
	v2 operator -= (v2& a, v2&b);
	v2 operator += (v2& a, v2&b);


//-----------
//----v3-----
//-----------
	v3 operator + (v3& a, v3&b);
	v3 operator - (v3& a, v3&b);
	v3 operator * (v3& a, v3&b);
	v3 operator / (v3& a, v3&b);

	v3 operator *= (v3& a, v3&b);
	v3 operator /= (v3& a, v3&b);
	v3 operator -= (v3& a, v3&b);
	v3 operator += (v3& a, v3&b);

	v3 operator + (v3& a, f32 value);
	v3 operator - (v3& a, f32 value);
	v3 operator * (v3& a, f32 value);
	v3 operator / (v3& a, f32 value);

	v3 operator *= (v3& a, f32 value);
	v3 operator /= (v3& a, f32 value);
	v3 operator -= (v3& a, f32 value);
	v3 operator += (v3& a, f32 value);

	f32 Length(v3& a);
	f32 Dot(v3& a, v3& b);
	v3  Cross(v3& a, v3& b);
	v3  Normalize(v3 a);

//-----------
//----v4-----
//-----------
	v4 operator + (v4& a, v4&b);
	v4 operator - (v4& a, v4&b);
	v4 operator * (v4& a, v4&b);
	v4 operator / (v4& a, v4&b);

	v4 operator *= (v4& a, v4&b);
	v4 operator /= (v4& a, v4&b);
	v4 operator -= (v4& a, v4&b);
	v4 operator += (v4& a, v4&b);

	std::ostream& operator << (std::ostream& os, v2& v);
	std::ostream& operator << (std::ostream& os, v3& v);
	std::ostream& operator << (std::ostream& os, v4& v);

	f32 Length(v2& a);
	f32 Dot(v2& a, v2& b);

	f32 Length(v4& a);
	f32 Dot(v4& a, v4& b);
}