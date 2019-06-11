#pragma once

namespace Craft
{
	class CRAFT_API FileSystem
	{
	public:
		static bool FileExist(String& fileName);
		static s64 GetFileSize(String& fileName);

		static byte* ReadFile(String& fileName, u64& size);
		static bool WriteFile(String& fileName, byte* byffer, u64 size);
	};
}