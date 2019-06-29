#pragma once

#include "Craft\System\FileSystem.h"
#include "Craft\Graphics\Image\ImageHeaders.h"

namespace Craft
{
	enum class ImageType
	{
		BMP
	};

	struct Image
	{
		s32 Width;
		s32 Height;
		ImageType Type;

		u32* Pixels;

		Image(u32 width, u32 height, u32* pixels, ImageType type) :
			Width(width),
			Height(height),
			Pixels(pixels),
			Type(type)
		{
		}

		~Image()
		{
			Release();
		}

		void Release()
		{
			if (!m_IsReleased) 
			{
				m_IsReleased = true;
				free(Pixels);
			}
		}

	private:
		bool m_IsReleased;

	};

	class ImageLoader
	{
	public:

		Image* LoadBMPImage(String path)
		{
			u64 size;
			BitmapHeader* bitmap = (BitmapHeader*)FileSystem::ReadFromFile(path, size);

			CR_ASSERT(bitmap, "Can't load file");

			Image* image = new Image(
				bitmap->Width,
				bitmap->Height,
				((u32*)bitmap + bitmap->BitmapOffset),
				ImageType::BMP);

			return image;
		}
	};
}