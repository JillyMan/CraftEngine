#include "crpch.h"
#include "VFS.h"

#include <fstream>
#include <streambuf>

namespace Craft { namespace System {
	Vfs::Vfs(String root) : m_Root(root)
	{
	}

	Image* Vfs::GetImage(String& path)
	{
		return ImageLoader::LoadBMPImage(GetFullPath(path));
	}

	String Vfs::LoadFileString(String& path) {
		// pls man investigate this line in future.
		std::string result(static_cast<std::stringstream const&>(std::stringstream() << std::ifstream(GetFullPath(path)).rdbuf()).str());
		return result;
	}
}}