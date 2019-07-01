#pragma once

namespace Craft
{
	//Specify numbers of color component in the texture
	enum class InternalPixelType
	{
		RGB,
		RGBA,
	};

	enum class ImageType
	{
		BMP
	};

	struct Image
	{
		s32 Width;
		s32 Height;
		ImageType Type;
		InternalPixelType InternalType;
		u8* Pixels;

		Image(u32 width, u32 height, void* formatData, u32 pixelsOffset, ImageType type, InternalPixelType internalType) :
			Width(width),
			Height(height),
			Pixels((u8*)formatData + pixelsOffset),
			FormatData(formatData),
			Type(type),
			InternalType(internalType)
		{
		}

		~Image()
		{
			Release();
		}

		template<class T>
		T* GetFormatData()
		{
			return (T*)FormatData;
		}

		void Release()
		{
			if (!m_IsReleased)
			{
				m_IsReleased = true;
				free(FormatData);
			}
		}

	private:
		void* FormatData;
		bool m_IsReleased;
	};
}