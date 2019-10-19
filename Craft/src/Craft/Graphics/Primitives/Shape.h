#pragma once

#include <Craft/Graphics/Shader.h>
#include <Craft/Graphics/Buffer.h>
#include <Craft/Graphics/Texture.h>
#include <Craft/Graphics/VertexArray.h>
#include <Craft/Graphics/Image/Image.h>
#include <Craft/Graphics/Primitives/Mesh.h>

namespace Craft { namespace Graphics {
	
	class Shape
	{
	protected:
		f32 m_Rotation = 0;
		v3 m_Axis = v3(1.0f, 1.0f, 1.0f);
		v3 m_Scale = v3(1.0f, 1.0f, 1.0f);
		v3 m_Origin;
		v3 m_Position;
		v4 m_Color;

		mat4 m_ModelMatrix = mat4::Identity();
		mat4 m_ViewProjectionMatrix;

		mat4 m_ViewMatrix;
		mat4 m_ProjectionMatrix;

		Shader* m_Shader;
		Texture* m_Texture;
		VertexArray* m_VertexArray;

	public:
		Shape(v3 pos, Image& image) :
			m_Shader(NULL),
			m_Texture(NULL),
			m_VertexArray(NULL)
		{
			SetPosition(pos);
			SetImage(image);
		}

		virtual ~Shape()
		{
			delete m_Shader;
			delete m_Texture;
			delete m_VertexArray;
		}

		virtual void BeginDraw() = 0;
		virtual void EndDraw() = 0;

	public:
		void SetViewProjectionMatrix(mat4& matrix) 
		{
			m_ViewProjectionMatrix = matrix;
		}

		void SetProjectionMatrix(mat4& matrix)
		{
			m_ProjectionMatrix = matrix;
		}

		void SetViewMatrix(mat4& matrix)
		{
			m_ViewMatrix = matrix;
		}

		void SetColor(Craft::v4& color) 
		{
			m_Color = color; 
		}

		void SetPosition(v3& position) 
		{ 
			m_Position = position; 
			RecalculateModelMatrix(); 
		}

		void SetImage(Image& image) 
		{ 
			m_Texture = Texture::Create(TextureType::Texture2D);
			m_Texture->Bind();
			m_Texture->SetParameteri(TextureParameterName::MinFilter, TextureParameter::Linear);
			m_Texture->SetParameteri(TextureParameterName::MagFilter, TextureParameter::Linear);
			m_Texture->SetImage(image);
		}

		void SetRotation(f32 rotation, v3& axis)
		{
			m_Rotation = rotation;
			m_Axis = axis;
			RecalculateModelMatrix();
		}

		void SetScale(v3& scale) { m_Scale = scale; RecalculateModelMatrix(); }
		inline VertexArray* GetVertexArray() const { return m_VertexArray; }

	private:
		void RecalculateModelMatrix()
		{
			m_ModelMatrix = mat4::VeiwModelMatrix(m_Position, m_Scale, m_Rotation, m_Axis);
		}
	};
} }