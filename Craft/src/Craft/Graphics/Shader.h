#pragma once

struct v2;
struct v3;
struct v4;

namespace Craft
{
	class Shader
	{
	public:
		virtual void Use() = 0;
		virtual void Unuse() = 0;

		virtual void SetUniform1f(const char* name, f32 value) = 0;
		virtual void SetUniform2f(const char* name, v2 value) = 0;
		virtual void SetUniform3f(const char* name, v3 value) = 0;
		virtual void SetUniform4f(const char* name, v4 value) = 0;
	};
}