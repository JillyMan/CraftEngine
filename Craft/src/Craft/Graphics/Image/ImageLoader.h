#pragma once

#include <Craft\System\FileSystem.h>
#include <Craft\Graphics\Image\Image.h>
#include <Craft\Graphics\Image\ImageHeaders.h>

namespace Craft
{
	// it's MOKE
	class ImageLoader
	{
	public:
		static Image* LoadBMPImage(String path)
		{
			u64 size;
			BitmapHeader* bitmapHeader = (BitmapHeader*)FileSystem::ReadFromFile(path, size);

			CR_ASSERT(bitmapHeader, "Can't load file");

			Image* image = new Image(
				bitmapHeader->Width,
				bitmapHeader->Height,
				(void*)bitmapHeader,
				bitmapHeader->BitmapOffset,
				ImageType::BMP,
				InternalPixelType::RGB);

			return image;
		}
	};
}