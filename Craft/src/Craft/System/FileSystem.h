#pragma once

namespace Craft
{
	class CRAFT_API FileSystem
	{
	public:
		static bool FileExist(String& fileName);
		static s64 GetFileSize(String& fileName);

		static byte* ReadFromFile(String& fileName, u64& size);
		static bool WriteToFile(String& fileName, byte* buffer, u64 bytesToWrite);
	};
}