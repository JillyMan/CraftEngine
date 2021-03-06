#pragma once

namespace Craft
{
#pragma pack(push, 1)
	struct BitmapHeader
	{
		u16  FileType;
		u32 FileSize;
		u16 Reserved1;
		u16 Reserved2;
		u32 BitmapOffset;
		u32 Size;
		s32 Width;
		s32 Height;
		u16 Planes;
		u16 BitsPerPixel;
		u32 Compression;
		u32 SizeOfBitmap;
		s32 HorzResolution;
		s32 VertResolution;
		u32 ColorsUsed;
		u32 ColorsImportant;

		u32 RedMask;
		u32 GreenMask;
		u32 BlueMask;
		u32 AlphaMask;
	};
#pragma pack(pop)
}