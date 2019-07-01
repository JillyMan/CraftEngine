#pragma once

#include <Craft\Graphics\Image\Image.h>

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
		LinearMipMapLinear,

		Linear,
		Nearest
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
		virtual void Bind(s32 index = 0) = 0;
		virtual void Unbind() = 0;
		virtual s32 GetIndex() = 0;

		virtual void SetImage(Image& image, bool isMipMap = true) = 0;
		virtual void SetParameterfv(TextureParameterName  param, f32* values) = 0;
		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) = 0;

		static Texture* Create(TextureType type);
	};
}