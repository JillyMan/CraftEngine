#include <Craft\Graphics\Texture.h>
#include <Platform\OpenGL\OpenGL.h>
#include <Craft\Graphics\Image\ImageLoader.h>

namespace Craft
{
	class OpenGLTexture2D : public Texture
	{
	private:
		GLuint m_TextureId;

	public:
		OpenGLTexture2D();
		~OpenGLTexture2D();
		virtual void Bind() override;
		virtual void Unbind() override;

		virtual void SetImage(Image& image, bool isMipMap = true) override;
		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) override;
		virtual void SetParameterfv(TextureParameterName paramName, f32* values) override;
	};
}