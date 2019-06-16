#pragma once

#include "vfs.h"

static bool g_IsInit = false;
static VFS_ErrorCode g_LastError = VFS_ERROR_NONE;
static VFS_PCSTR g_ErrorStrings[] =
{
	VFS_TEXT("No Error (VFS_ERROR_NONE)"),
	VFS_TEXT("VFS not initialized yet (VFS_ERROR_NOT_INITIALIZED_YET)"),
	VFS_TEXT("VFS already initialized (VFS_ERROR_ALREADY_INITIALIZED)"),
	VFS_TEXT("Entity already exists (VFS_ERROR_ALREADY_EXISTS)"),
	VFS_TEXT("Entity not found (VFS_ERROR_NOT_FOUND)"),
	VFS_TEXT("Invalid Parameter (VFS_ERROR_INVALID_PARAMETER)"),
	VFS_TEXT("Generic Error (VFS_ERROR_GENERIC)"),
	VFS_TEXT("Invalid Error Code (VFS_ERROR_INVALID_ERROR_CODE)"),
	VFS_TEXT("No Root Paths defined yet (VFS_ERROR_NO_ROOT_PATHS_DEFINED)"),
	VFS_TEXT("Permission denied (VFS_ERROR_PERMISSION_DENIED)"),
	VFS_TEXT("Entity in use (VFS_ERROR_IN_USE)"),
	VFS_TEXT("Can't manipulate Archives (VFS_ERROR_CANT_MANIPULATE_ARCHIVES)"),
	VFS_TEXT("Not an Archive (VFS_ERROR_NOT_AN_ARCHIVE)"),
	VFS_TEXT("Missing Filters (VFS_ERROR_MISSING_FILTERS)"),
	VFS_TEXT("Invalid Archive Format (VFS_ERROR_INVALID_ARCHIVE_FORMAT)")
};

static FilterMap g_Filters;

VFS_BOOL VFS_Init()
{
	if (!IsInit())
	{
		SetLastError(VFS_ERROR_NOT_INITIALIZED_YET);
		return VFS_FALSE;
	}

	g_Filters.clear();

	g_IsInit = VFS_TRUE;
	return VFS_TRUE;
}

VFS_BOOL IsInit()
{
	return g_IsInit;
}
