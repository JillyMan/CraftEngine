#include <crpch.h>

#include "OpenGLTexture.h"

namespace Craft { namespace Graphics {

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
		case TextureParameterName::S: return GL_TEXTURE_WRAP_S;
		case TextureParameterName::T: return GL_TEXTURE_WRAP_T;
		case TextureParameterName::R: return GL_TEXTURE_WRAP_R;
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
	GLenum ToOpenGLInternalType(InternalPixelType type)
	{
		switch (type)
		{
		case InternalPixelType::RGB: return GL_RGB;
		case InternalPixelType::RGBA: return GL_RGBA;
		}

		CR_ASSERT(false, "Invalid internal type!");
		return GL_NONE;
	}

	Texture* Texture::Create(TextureType type)
	{
		switch (type)
		{
			//case TextureType::Texture1D: return new OpenGLTexture1D();
		case TextureType::Texture2D: return new OpenGLTexture2D();
			//case TextureType::Texture3D: return new OpenGLTexture3D();
		}

		CR_ASSERT(false, "Type not found");
		return nullptr;
	}

	OpenGLTexture2D::OpenGLTexture2D()
	{
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureId);
	}

	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureId);
	}

	void OpenGLTexture2D::Bind(s32 index)
	{
		m_BlockIndex = index;
		glActiveTexture(GL_TEXTURE0 + index);
		glBindTexture(GL_TEXTURE_2D, m_TextureId);
	}

	void OpenGLTexture2D::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}

	void OpenGLTexture2D::SetImage(Image& image, bool isMipMap)
	{
		glTexImage2D(GL_TEXTURE_2D,
			0,
			ToOpenGLInternalType(image.InternalType),
			image.Width, image.Height,
			0,
			//---------need fix------------------
			GL_BGR,
			//-----------------------------------
			GL_UNSIGNED_BYTE,
			//-----------------------------------
			image.Pixels);

		if (isMipMap)
		{
			glGenerateMipmap(GL_TEXTURE_2D);
		}
	}

	void OpenGLTexture2D::SetParameteri(TextureParameterName paramName, TextureParameter param)
	{
		glTextureParameteri(m_TextureId, ToOpenGLParameterName(paramName), ToOpenGLParameter(param));
	}

	void OpenGLTexture2D::SetParameterfv(TextureParameterName paramName, f32* values)
	{
		glTextureParameterfv(m_TextureId, ToOpenGLParameterName(paramName), values);
	}
}}