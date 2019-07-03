#pragma once

namespace Craft
{
	struct mat4
	{
		mat4() 
		{
			for (int i = 0; i < 16; ++i)
			{
				e[i] = 0;
			}
		}

		f32& operator [] (int index) { return e[index]; }

		mat4 operator + (mat4& b);
		mat4 operator - (mat4& b);
		mat4 operator * (mat4& b);

		friend mat4 operator += (mat4& a, mat4& b);
		friend mat4 operator -= (mat4& a, mat4& b);
		friend mat4 operator *= (mat4& a, mat4& b);
		friend std::ostream& operator << (std::ostream& os, mat4& mat);

		friend mat4 Identity(f32 value = 1.0f);
		friend mat4 Rotate(f32 angle);

		f32 e[16];
	};
}