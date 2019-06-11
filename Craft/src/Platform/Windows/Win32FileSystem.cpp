#include "crpch.h"
#include "Craft\System\FileSystem.h"

namespace Craft
{
	bool FileSystem::FileExist(String& fileName)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);		
		bool Result = false;
		if (FileHandle)
		{
			Result = true;
			CloseHandle(FileHandle);
		}

		return Result;
	}
	
	s64 FileSystem::GetFileSize(String& fileName)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		s64 Result = 0;
		if (FileHandle)
		{
			LARGE_INTEGER FileSize;
			GetFileSizeEx(FileHandle, &FileSize);
			Result = FileSize.QuadPart;
			
			CloseHandle(FileHandle);
		}

		return Result;
	}

	byte* ReadFile(String& fileName, u64& size)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		byte* Result = nullptr;

		if (FileHandle)
		{
			LARGE_INTEGER FileSize;
			if (GetFileSizeEx(FileHandle, &FileSize))
			{
				s64 FileSize64 = FileSize.QuadPart;
				Result = (byte*)malloc(FileSize64);
				s64 BytesRead;
				if (ReadFile(FileHandle, Result, FileSize64, &BytesRead, 0))
				{

				}

				if (FileSize64 != BytesRead)
				{
					free(Result);
					//TODO: need handle
				}
			}
			else
			{
				//TODO need handle.... GetLastError() 
			}

			CloseHandle(FileHandle);
		}
		return Result;
	}
	
	bool FileSystem::WriteFile(String& fileName, byte* byffer, u64 size)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		BOOL Result = FALSE;

		if (FileHandle)
		{
			DWORD WriteSize = 0;
		}
	}
}