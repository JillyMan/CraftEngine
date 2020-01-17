#pragma once

#include <Craft/Graphics/Image/ImageLoader.h>

namespace Craft { namespace System {
	class Vfs {
	private:
		String m_Root;

	public:
		Vfs(String root);

		Image* GetImage(String& path);
		String LoadFileString(String& path);
	private:
		String GetFullPath(String& path) const { return m_Root + path; }
	};
} }