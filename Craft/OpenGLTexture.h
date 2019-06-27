#include <Craft\Graphics\Texture.h>
#include <Platform\OpenGL\OpenGL.h>

namespace Craft
{
	static GLenum ToOpenGLTextureType(TextureType type)
	{
		switch (type)
		{
			case TextureType::Texture1D: return GL_TEXTURE_1D;
			case TextureType::Texture2D: return GL_TEXTURE_2D;
			case TextureType::Texture3D: return GL_TEXTURE_3D;
		}

		CR_ASSERT(false, "Invalid texture type!");
		return GL_NONE;
	}

	static GLenum ToOpenGLParameterName(TextureParameterName name)
	{
		switch (name)
		{
			case TextureParameterName::S : return GL_TEXTURE_WRAP_S;
			case TextureParameterName::T : return GL_TEXTURE_WRAP_T;
			case TextureParameterName::R : return GL_TEXTURE_WRAP_R;
			case TextureParameterName::TextureBorderColor: return GL_TEXTURE_BORDER_COLOR;
		}

		CR_ASSERT(false, "Invalid texture parameter name!");
		return GL_NONE;
	}

	static GLenum ToOpenGLParameter(TextureParameter param)
	{
		switch (param)
		{
			case TextureParameter::ClampToBorder: return GL_CLAMP_TO_BORDER;
			case TextureParameter::ClampTPEdge: return GL_CLAMP_TO_EDGE;
			case TextureParameter::MirroredRepeat: return GL_MIRRORED_REPEAT;
			case TextureParameter::Repeat: return GL_REPEAT;
		}

		CR_ASSERT(false, "Invalid texture parameter name!");
		return GL_NONE;
	}

	class OpenGLTexture : public Texture
	{
	private:
		TextureType m_Type;
		GLenum m_OpenGLType;
		GLuint m_TextureId;

	public:

		OpenGLTexture(TextureType type) :
			m_Type(type), m_OpenGLType(ToOpenGLTextureType(type))
		{
			glCreateTextures(m_OpenGLType, 1, &m_TextureId);
		}

		virtual void Bind() override
		{
			
		}
		
		virtual void Unbind() override
		{
			
		}

		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) override
		{
			glTexParameteri(m_TextureId, ToOpenGLParameterName(paramName), ToOpenGLParameter(param));
		}

		virtual void SetParameterfv(TextureParameter param, f32* values) override
		{
			
		}
	};
}