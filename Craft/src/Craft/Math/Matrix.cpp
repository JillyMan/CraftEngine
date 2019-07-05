#include "crpch.h"
#include "Matrix.h"
#include "Vectors.h"

namespace Craft
{
	mat4 mat4::operator + (mat4& b)
	{
		mat4 result;
		for (int i = 0; i < 16; i++)
		{
			result[i] = e[i] + b[i];
		}
		return result;
	}

	mat4 mat4::operator - (mat4& b)
	{
		mat4 result;
		for (int i = 0; i < 16; i++)
		{
			result[i] = e[i] - b[i];
		}
		return result;
	}

	mat4 operator += (mat4& a, mat4& b)
	{
		a = a + b;
		return a;
	}

	mat4 operator -= (mat4& a, mat4& b)
	{
		a = a - b;
		return a;
	}

	mat4 mat4::operator*(mat4& b)
	{
		mat4 result;
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				f32 sum = 0.0f;
				for(int k = 0; k < 4; ++k)
				{
					sum += e[i + j * 4] * b[j + k * 4];
				}
				result[i + j * 4] = sum;
			}
		}

		return result;
	}

	mat4 operator *= (mat4& a, mat4& b)
	{
		a = a * b;
		return a;
	}

	mat4 mat4::Translate(v3& v)
	{
		mat4 result;
		result[3 + 4 * 0] = v.x;
		result[3 + 4 * 1] = v.y;
		result[3 + 4 * 2] = v.z;
		result[3 + 4 * 3] = 1.0f;
		return result;
	}

	mat4 mat4::Scale(v3& v)
	{
		mat4 result;
		result[0 + 4 * 0] = v.x;
		result[1 + 4 * 1] = v.y;
		result[2 + 4 * 2] = v.z;
		result[3 + 4 * 3] = 1.0f;
		return result;
	}

	mat4 mat4::Identity(f32 value)
	{
		mat4 result;
		result[0 + 4 * 0] = value;
		result[1 + 4 * 1] = value;
		result[2 + 4 * 2] = value;
		result[3 + 4 * 3] = value;
		return result;
	}

	mat4 mat4::Rotate(f32 angle, v3 axis)
	{
		mat4 result;
		return result;
	}

	std::ostream& operator << (std::ostream& os, mat4& mat)
	{
		for (int i = 0; i < 4; ++i)
		{
			for (int j = 0; j < 4; ++j)
			{
				os << mat[j + i*4] << " ";
			}
			os << std::endl;
		}
		return os;
	}
}