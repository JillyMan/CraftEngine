#pragma once

namespace Craft
{
	//Specify bihevior when texture coords out of range

	enum class TextureParameter
	{
		None,
		Repeat,
		MirroredRepeat,
		ClampTPEdge,
		ClampToBorder
	};

	enum class TextureParameterName
	{
		S,
		T,
		R,
		TextureBorderColor
	};

	enum class TextureType
	{
		Texture1D,
		Texture2D,
		Texture3D
	};

	class Texture
	{
	public:
		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		virtual void SetParameterfv(TextureParameter param, f32* values) = 0;
		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) = 0;
	};
}