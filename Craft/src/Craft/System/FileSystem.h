#pragma once

namespace Craft
{
	class CRAFT_API FileSystem
	{
	public:
		static bool FileExist(String& fileName);
		static s64 GetFileSize(String& fileName);

		static u8* ReadFromFile(String& fileName, u64& size);
		static bool WriteToFile(String& fileName, u8* buffer, u64 bytesToWrite);
	};
}