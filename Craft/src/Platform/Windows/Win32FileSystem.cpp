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

	//When Result unused, need call free(data);
	s8* FileSystem::ReadFromFile(String& fileName, u64& size)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		s8* Result = nullptr;

		if (FileHandle)
		{
			s64 FileSize = GetFileSizeInternal(FileHandle);
			if (FileSize)
			{	
				//TODO (use another allocator)
				Result = (s8*)malloc(FileSize);

				DWORD BytesRead;
				if (ReadFile(FileHandle, Result, FileSize, &BytesRead, 0) && 
					FileSize == BytesRead)
				{
					size = FileSize;
				}
				else
				{
					CR_WARN("Can't read, win32-error-code: [%d]", GetLastError());
					free(Result);
				}
			}

			CloseHandle(FileHandle);
		}
		else
		{
			CR_ERROR("Can't find file [%d]", fileName);
		}

		return Result;
	}
	
	bool FileSystem::WriteToFile(String& fileName, s8* buffer, u64 bytesToWrite)
	{
		HANDLE FileHandle = CreateFile(fileName.c_str(), GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
		BOOL Result = FALSE;

		if (FileHandle)
		{
			DWORD WriteSize = 0;
			if (!WriteFile(FileHandle, buffer, bytesToWrite, &WriteSize, 0))
			{
				CR_ERROR("Can't write to file");
			}	

			Result = WriteSize == bytesToWrite;

			CloseHandle(FileHandle);
		}
		else
		{
			CR_WARN("Can't find file [%s]", fileName.c_str());
		}
		return Result;
	}
}