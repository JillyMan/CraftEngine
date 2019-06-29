#pragma once

namespace Craft
{
	//Specify bihevior when texture coords out of range
	enum class TextureParameter
	{
		None,

		Repeat,
		ClampTPEdge,
		ClampToBorder,
		MirroredRepeat,

		NearesetMipMapNearset,
		NearestMipMapLinear,
		LinearMipMapNearest,
		LinearMipMapLinear
	};

	enum class TextureParameterName
	{
		S,
		T,
		R,
		MagFilter,
		MinFilter,
		TextureBorderColor,
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

		virtual void SetParameterfv(TextureParameterName  param, f32* values) = 0;
		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) = 0;
	};
}