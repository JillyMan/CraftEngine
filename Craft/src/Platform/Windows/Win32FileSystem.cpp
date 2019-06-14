#include "crpch.h"
#include "Craft\System\FileSystem.h"

namespace Craft
{
	static s64 GetFileSizeInternal(HANDLE FileHandle)
	{
		s64 Result = 0;
		if (FileHandle)
		{
			LARGE_INTEGER FileSize;
			GetFileSizeEx(FileHandle, &FileSize);
			Result = FileSize.QuadPart;
		}
		return Result;
	}

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
		s64 Result = GetFileSizeInternal(FileHandle);
		CloseHandle(FileHandle);
		return Result;
	}

	//When Result unused her need a clear (call free(data));
	u8* FileSystem::ReadFromFile(String& fileName, u64& size)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		u8* Result = nullptr;

		if (FileHandle)
		{
			s64 FileSize = GetFileSizeInternal(FileHandle);
			if (FileSize)
			{	
				//TODO(use another allocator)
				Result = (u8*)malloc(FileSize);

				DWORD BytesRead;
				if (!ReadFile(FileHandle, Result, FileSize, &BytesRead, 0) && 
					FileSize != BytesRead)
				{
					free(Result);
				}
			}
			else
			{
				//TODO need handle.... GetLastError() 
			}

			CloseHandle(FileHandle);
		}
		else
		{
			//CR_ERROR("Can't find file {0}", fileName);
		}

		return Result;
	}
	
	bool FileSystem::WriteToFile(String& fileName, u8* buffer, u64 bytesToWrite)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		BOOL Result = FALSE;

		if (FileHandle)
		{
			DWORD WriteSize = 0;
			if (!WriteFile(FileHandle, buffer, bytesToWrite, &WriteSize, 0) &&
				WriteSize != bytesToWrite)
			{
				CR_ERROR("Can't write to file");
			}	

			CloseHandle(FileHandle);
		}
		return Result;
	}
}