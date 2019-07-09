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

		Shape(Craft::v4 color) :
			m_Color(color)
		{
		}

		virtual ~Shape() = default;

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
	};
}