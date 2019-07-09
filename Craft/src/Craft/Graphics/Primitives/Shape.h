#pragma once

#include "../Shader.h"
#include "../Buffer.h"
#include "../VertexArray.h"
#include "../Texture.h"

namespace Craft
{
	class Shape
	{
	protected:
		v4 m_Color;
		mat4 viewProjectionMatrix;

	public:
		Shader* shader;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;

		std::vector<Craft::Texture*> m_Textures;

		Shape(Craft::v4& color) :
			m_Color(color)
		{
		}

		virtual ~Shape()
		{
			FreeResources();
		}

		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

	public:
		void SetColor(Craft::v4 color)
		{
			m_Color = color;
		}

		void SetViewProjectinMatrix(mat4& matrix)
		{
			viewProjectionMatrix = matrix;
		}

	protected:
		void TexturesInit(std::vector<Craft::Image*> images)
		{
			for (Craft::Image* image : images)
			{
				Craft::Texture* texture = Craft::Texture::Create(Craft::TextureType::Texture2D);
				texture->Bind();
				texture->SetParameteri(Craft::TextureParameterName::MinFilter, Craft::TextureParameter::Linear);
				texture->SetParameteri(Craft::TextureParameterName::MagFilter, Craft::TextureParameter::Linear);
				texture->SetImage(*image);
				m_Textures.push_back(texture);
			}
		}

	protected:
		virtual void FreeResources()
		{
			for (s32 i = 0; i < m_Textures.size(); ++i)
			{
				delete m_Textures[i];
			}

			delete shader;
			delete vertexArray;
			delete vertexBuffer;
			delete indexBuffer;
		}
	};
}