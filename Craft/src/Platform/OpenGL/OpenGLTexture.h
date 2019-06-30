#include <Craft\Graphics\Texture.h>
#include <Platform\OpenGL\OpenGL.h>
#include <Craft\Graphics\Image\ImageLoader.h>

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


			case TextureParameter::Linear: return  GL_LINEAR;
			case TextureParameter::Nearest: return  GL_NEAREST;
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
		GLenum m_DimensionType;
		GLuint m_TextureId;

	public:

		//TODO: make class incapsulated info about image

		OpenGLTexture(TextureType type, Image* image, bool isMipMap = false) :
			m_Type(type), m_DimensionType(ToOpenGLTextureType(type))
		{
			glCreateTextures(m_DimensionType, 1, &m_TextureId);

			// need delet bgr
			glTexImage2D(m_DimensionType,
				0, 
				GL_RGB, 
				image->Width, image->Height, 
				0,
				GL_RGB,
				GL_UNSIGNED_BYTE,
				image->Pixels);

			if (isMipMap)
			{
				glGenerateMipmap(m_DimensionType);
			}
		}

		virtual void Bind() override
		{
			// add define in glew
			glBindTexture(m_DimensionType, m_TextureId);
		}
		
		virtual void Unbind() override
		{
			glBindTexture(m_DimensionType, 0);
		}

		virtual void SetParameteri(TextureParameterName paramName, TextureParameter param) override
		{
			glTextureParameteri(m_TextureId, ToOpenGLParameterName(paramName), ToOpenGLParameter(param));
		}

		virtual void SetParameterfv(TextureParameterName paramName, f32* values) override
		{
			glTextureParameterfv(m_TextureId, ToOpenGLParameterName(paramName), values);
		}
	};
}