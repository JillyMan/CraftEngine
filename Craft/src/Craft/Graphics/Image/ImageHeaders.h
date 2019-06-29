#pragma once

namespace Craft
{
#pragma pack(push, 1)
	struct BitmapHeader
	{
		WORD  FileType;
		DWORD FileSize;
		WORD  Reserved1;
		WORD  Reserved2;
		DWORD BitmapOffset;
		DWORD Size;
		LONG  Width;
		LONG  Height;
		WORD  Planes;
		WORD  BitsPerPixel;
	};
#pragma pack(pop)
}