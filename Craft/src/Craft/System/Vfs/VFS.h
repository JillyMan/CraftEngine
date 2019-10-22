#pragma once

#include <Craft/Graphics/Image/ImageLoader.h>

namespace Craft { namespace Vfs {
	class Vfs {
	private:
		String m_Root;

	public:
		Vfs(String root) : m_Root(root)
		{
		}

		Image* GetImage(String path)
		{
			return ImageLoader::LoadBMPImage(m_Root + path);
		}
	};
} }