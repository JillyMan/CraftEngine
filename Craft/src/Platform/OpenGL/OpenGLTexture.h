#include <Platform\OpenGL\OpenGL.h>
#include <Craft\Graphics\Texture.h>
#include <Craft\Graphics\Image\ImageLoader.h>

namespace Craft { namespace Graphics {

	class OpenGLTexture2D : public Texture
	{
	private:
		GLuint m_TextureId;
		s32 m_BlockIndex;

	public:
		OpenGLTexture2D();
		~OpenGLTexture2D();
		virtual void Bind(s32 index = 0) override;
		virtual void Unbind() override;

		virtual s32 GetIndex() { return m_BlockIndex; }

		virtual void SetImage(Image& image, bool isMipMap = true) override;
		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) override;
		virtual void SetParameterfv(TextureParameterName paramName, f32* values) override;
	};

}}