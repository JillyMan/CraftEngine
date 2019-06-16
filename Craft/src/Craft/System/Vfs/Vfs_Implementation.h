#pragma once

#include "vfs.h"

typedef std::map< VFS_String, VFS_Filter* > FilterMap;

void SetLastError(VFS_ErrorCode error);
