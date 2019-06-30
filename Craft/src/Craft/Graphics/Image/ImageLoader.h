#pragma once

#include <Craft\System\FileSystem.h>
#include <Craft\Graphics\Image\Image.h>
#include <Craft\Graphics\Image\ImageHeaders.h>

namespace Craft
{
	class ImageLoader
	{
	public:

		static Image* LoadBMPImage(String path)
		{
			u64 size;
			BitmapHeader* bitmap = (BitmapHeader*)FileSystem::ReadFromFile(path, size);

			CR_ASSERT(bitmap, "Can't load file");

			Image* image = new Image(
				bitmap->Width,
				bitmap->Height,
				(void*)bitmap,
				bitmap->BitmapOffset,
				ImageType::BMP);

			return image;
		}

	private:
		static Image* GetBMP()
		{

		}
	};
}