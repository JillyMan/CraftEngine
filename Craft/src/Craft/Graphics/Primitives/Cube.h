#pragma once

#include <Craft/Graphics/Primitives/Shape.h>

#include <Platform/OpenGL/OpenGLShader.h>
#include <Craft/Graphics/Shaders/ShaderFactory.h>

namespace Craft { namespace Graphics {


	class Cube : public Shape
	{
	public:
		Cube(v3& pos, Image& image) :
			Shape(pos, image)
		{
			InitTextureCube();
			m_Shader = new OpenGLShader(GetVertexWithTextureShader(), GetFragmentWithTextureShader());
		}

		Cube(v3& pos, v4& color) :
			Shape(pos, color)
		{
		}

		virtual void BeginDraw() override
		{
			m_Shader->Use();
			m_VertexArray->Bind();

			if (m_Texture != NULL)
			{
				m_Texture->Bind(0);
				String name(TEXTURE_STRING);
				name.append("0");
				m_Shader->SetUniform1i(name.c_str(), 0);
			}
			else
			{
				m_Shader->SetUniform4f(U_COLOR_STRING, m_Color);
			}
			m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
			m_Shader->SetUniformMatrix4fv(VIEW_MATRIX_STRING, m_ViewMatrix);
			m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ProjectionMatrix);
		}

		virtual void EndDraw() override
		{
		}

	private:
		void InitTextureCube()
		{
			//m_Mesh = Mesh::GenerateCubeWithTextureCoord();
			f32 vertices[] = {
				0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
				1.0f, 0.0f, 0.0f, 1.0f, 0.0f,
				1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				0.0f, 1.0f, 1.0f, 0.0f, 1.0f,
				1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
				1.0f, 0.0f, 1.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
			};

			u32 indices[] = {
				0, 2, 1, //face front
				0, 3, 2,
				2, 3, 4, //face top
				2, 4, 5,
				1, 2, 5, //face right
				1, 5, 6,
				0, 7, 4, //face left
				0, 4, 3,
				5, 4, 7, //face back
				5, 7, 6,
				0, 6, 7, //face bottom
				0, 1, 6
			};

			BufferElement pos("Position", VertexDataType::Float3);
			BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);
			BufferLayout layout(std::vector<BufferElement> { pos, textCoord1 });

			VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));
			vertexBuffer->SetLayout(layout);

			m_VertexArray = VertexArray::Create();
			m_VertexArray->AddVertexBuffer(vertexBuffer);

			m_VertexArray->SetIndexBuffer(
				IndexBuffer::Create(indices, ArrayCount(indices))
			);
		}
	};

} }