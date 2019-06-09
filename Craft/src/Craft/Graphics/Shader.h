#pragma once

namespace Craft
{
	class Shader
	{
	public:
		virtual void Use() = 0;
		virtual void Unuse() = 0;
	};
}