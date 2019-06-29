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
			case TextureParameterName::MagFilter: return GL_TEXTURE_MAG_FILTER;
			case TextureParameterName::MinFilter: return GL_TEXTURE_MIN_FILTER;
			case TextureParameterName::TextureBorderColor: return GL_TEXTURE_BORDER_COLOR;
		}

		CR_ASSERT(false, "Invalid texture parameter name!");
		return GL_NONE;
	}

	static GLenum ToOpenGLParameter(TextureParameter param)
	{
		switch (param)
		{
			case TextureParameter::Repeat: return GL_REPEAT;
			case TextureParameter::ClampTPEdge: return GL_CLAMP_TO_EDGE;
			case TextureParameter::ClampToBorder: return GL_CLAMP_TO_BORDER;
			case TextureParameter::MirroredRepeat: return GL_MIRRORED_REPEAT;

			case TextureParameter::NearesetMipMapNearset: return GL_NEAREST_MIPMAP_NEAREST;
			case TextureParameter::NearestMipMapLinear: return GL_NEAREST_MIPMAP_LINEAR;
			case TextureParameter::LinearMipMapNearest: return GL_LINEAR_MIPMAP_NEAREST;
			case TextureParameter::LinearMipMapLinear: return  GL_LINEAR_MIPMAP_LINEAR;
		}

		CR_ASSERT(false, "Invalid texture parameter name!");
		return GL_NONE;
	}

	//TODO: Temp enum, need move to image class

	enum class PixelType
	{
		RGB,
		RGBA,
		BGR,
		BGRA
	};

	GLenum ToOpenGLPixelType(PixelType type)
	{
		switch (type)
		{
			case PixelType::RGB: return GL_RGB;
			case PixelType::RGBA: return GL_RGBA;
			case PixelType::BGR: return GL_BGR;
			case PixelType::BGRA: return GL_BGRA;
		}
		CR_ASSERT(false, "Invalid type!");
		return GL_NONE;
	}

	class OpenGLTexture : public Texture
	{
	private:
		TextureType m_Type;

		// emm all time for binding need get this value???? -- it's bad 
		GLenum m_OpenGLType;
		GLuint m_TextureId;

	public:

		//TODO: make class incapsulated info about image
		OpenGLTexture(TextureType type, bool isMipMap, char* image, u32 width, u32 height) :
			m_Type(type), m_OpenGLType(ToOpenGLTextureType(type))
		{
			glCreateTextures(m_OpenGLType, 1, &m_TextureId);

//			glTexImage2D(m_TextureId, width*height, ,width, height, )

			if (isMipMap)
			{
				glGenerateMipmap(m_TextureId);
			}
		}

		virtual void Bind() override
		{
			glBindTexture(m_OpenGLType, m_TextureId);
		}
		
		virtual void Unbind() override
		{
			glBindTexture(m_OpenGLType, 0);
		}

		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) override
		{
			glTexParameteri(m_TextureId, ToOpenGLParameterName(paramName), ToOpenGLParameter(param));
		}

		virtual void SetParameterfv(TextureParameterName paramName, f32* values) override
		{
			glTexParameterfv(m_TextureId, ToOpenGLParameterName(paramName), values);
		}
	};
}