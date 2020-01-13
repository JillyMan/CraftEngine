#pragma once

#include <Craft\Math\Math.h>

namespace Craft { namespace Graphics {

	class Shader
	{
	public:
		virtual void Use() = 0;
		virtual void Unuse() = 0;

		virtual void SetUniform1i(const char* name, s32 value) = 0;

		virtual void SetUniform1f(const char* name, f32 value) = 0;
		virtual void SetUniform2f(const char* name, v2& v) = 0;
		virtual void SetUniform3f(const char* name, v3& v) = 0;
		virtual void SetUniform4f(const char* name, v4& v) = 0;

		virtual void SetUniformMatrix4fv(const char* name, mat4& mat) = 0;
	};
} }