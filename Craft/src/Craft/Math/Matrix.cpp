#include "crpch.h"

#include <Craft/Math/Math.h>

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

		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				float sum = 0.0;
				for (int k = 0; k < 4; k++) {
					sum += e[j + k * 4] * b[k + i * 4];
				}
				result[j + i * 4] = sum;
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
		mat4 result = Identity();
		result[0 + 3 * 4] = v.x;
		result[1 + 3 * 4] = v.y;
		result[2 + 3 * 4] = v.z;
		return result;
	}

	mat4 mat4::Scale(v3& v)
	{
		mat4 result;
		result[0 + 0 * 4] = v.x;
		result[1 + 1 * 4] = v.y;
		result[2 + 2 * 4] = v.z;
		result[3 + 3 * 4] = 1.0f;
		return result;
	}

	mat4 mat4::Identity(f32 value)
	{
		mat4 result;
		result[0 + 0 * 4] = value;
		result[1 + 1 * 4] = value;
		result[2 + 2 * 4] = value;
		result[3 + 3 * 4] = value;
		return result;
	}

	mat4 mat4::Rotate(f32 angle, v3& axis)
	{
		mat4 result = Identity();

		f32 r = ToRadians(angle);
		f32 c = cos(r);
		f32 s = sin(r);
		f32 omc = 1.0f - c;

		f32 x = axis.x;
		f32 y = axis.y;
		f32 z = axis.z;

		result[0 + 4 * 0] = x * omc + c;
		result[1 + 4 * 0] = y * x * omc + z * s;
		result[2 + 4 * 0] = x * z * omc - y * s;

		result[0 + 4 * 1] = x * y * omc - z * s;
		result[1 + 4 * 1] = y * omc + c;
		result[2 + 4 * 1] = y * z * omc + x * s;

		result[0 + 4 * 2] = x * z * omc + y * s;
		result[1 + 4 * 2] = y * z * omc - x * s;
		result[2 + 4 * 2] = z * omc + c;

		return result;
	}

	mat4 mat4::Ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near, f32 far)
	{
		mat4 result;
		result[0 + 0 * 4] = 2.0f / (right - left);
		result[1 + 1 * 4] = 2.0f / (top - bottom);
		result[2 + 2 * 4] = 2.0f / (near - far);
		result[0 + 3 * 4] = (left + right) / (left - right);
		result[1 + 3 * 4] = (bottom + top) / (bottom - top);
		result[2 + 3 * 4] = (far + near) / (far - near);
		result[3 + 3 * 4] = 1.0f;

		return result;
	}

	mat4 mat4::Perspective(f32 fov, f32 aspectRatio, f32 near, f32 far)
	{
		mat4 result = Identity();
		f32 p = 1.0f / tanf(ToRadians(0.5f * fov));
		f32 a = p / aspectRatio;

		f32 b = (near + far) / (near - far);
		f32 c = (2.0f * near * far) / (near - far);

		result[0 + 0 * 4] = a;
		result[1 + 1 * 4] = p;
		result[2 + 2 * 4] = b;
		result[3 + 2 * 4] = -1.0f;
		result[2 + 3 * 4] = c;

		return result;
	}

	mat4 mat4::ModelMatrix(v3& pos, f32 rotation, v3& axis) 
	{
		mat4 result = mat4::Translate(pos) * mat4::Rotate(rotation, axis);
		return result;
	}

	mat4 mat4::ModelMatrix(v3& pos, v3& scale)
	{
		mat4 result = mat4::Translate(pos) * mat4::Scale(scale);
		return result;
	}

	mat4 mat4::ModelMatrix(v3& pos, v3& scale, f32 rotation, v3& axis)
	{
		mat4 result = mat4::Translate(pos) * mat4::Scale(scale) * mat4::Rotate(rotation, axis);
		return result;
	}

	mat4 mat4::LookAt(v3& pos, v3& target, v3& up)
	{
		v3 dir = pos - target;
		v3 camZ = Normalize(dir);
		v3 camX = Normalize(Cross(up, camZ));
		v3 camY = Cross(camZ, camX);

		mat4 view;
		view[0 + 0 * 4] = camX.x;
		view[1 + 0 * 4] = camX.y;
		view[2 + 0 * 4] = camX.z;

		view[0 + 1 * 4] = camY.x;
		view[1 + 1 * 4] = camY.y;
		view[2 + 1 * 4] = camY.z;

		view[0 + 2 * 4] = camZ.x;
		view[1 + 2 * 4] = camZ.y;
		view[2 + 2 * 4] = camZ.z;

		view[3 + 3 * 4] = 1.0f;

		mat4 transform = mat4::Translate(-pos);

		return view * transform;
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