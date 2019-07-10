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
		f32 m_Rotation;
		v3 m_Axis;
		v3 m_Scale;
		v3 m_Position;
		v3 m_Origin;
		v4 m_Color;

		mat4 m_ModelMatrix;
		mat4 m_ViewProjectionMatrix;

	public:
		Shader* shader;
		VertexArray* vertexArray;
		VertexBuffer* vertexBuffer;
		IndexBuffer* indexBuffer;

		std::vector<Craft::Texture*> m_Textures;

		Shape() :
			m_ModelMatrix(mat4::Identity()),
			m_Scale(1.0f, 1.0f, 1.0f),
			m_Axis(v3(1.0f, 1.0f, 1.0f)),
			m_Rotation(0)
		{
		}

		virtual ~Shape()
		{
			FreeResources();
		}

		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

	public:
		void SetViewProjectinMatrix(mat4& matrix) { m_ViewProjectionMatrix = matrix; }

		void SetColor(Craft::v4& color) { m_Color = color; }

		void SetPosition(v3& position) { m_Position = position; RecalculateModelMatrix(); }

		void SetRotation(f32 rotation, v3& axis)
		{
			m_Rotation = rotation;
			m_Axis = axis;
			RecalculateModelMatrix();
		}

		void SetScale(v3& scale) { m_Scale = scale; RecalculateModelMatrix(); }

	private:
		void RecalculateModelMatrix()
		{
			m_ModelMatrix = mat4::VeiwModelMatrix(m_Position, m_Scale, m_Rotation, m_Axis);
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