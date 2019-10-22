#pragma once

#include <Craft/Graphics/Primitives/Shape.h>

#include <Craft/Graphics/Shaders/ShaderFactory.h>
#include <Platform/OpenGL/OpenGLShader.h>

namespace Craft { namespace Graphics {

	class Sprite : public Shape
	{
	public:
		Sprite(f32 x, f32 y, f32 w, f32 h, Image& image) :
			Shape(v3(x, y, -1.0f), image)
		{
			SetPosition(v3(x, y, 0.0f));
			InitVertices(w, h);
		}

		Sprite(v3& pos, v2& size, v4& color) :
			Shape(pos, color)
		{
			InitVertices(size.x, size.y, pos.z);
		}

		virtual void BeginDraw() override
		{
			m_Shader->Use();
			//m_Texture->Bind(0);
			//String name(TEXTURE_STRING);
			//name.append("0");
			//m_Shader->SetUniform1i(name.c_str(), 0);

			m_Shader->SetUniform4f(U_COLOR_STRING, m_Color);
			m_Shader->SetUniformMatrix4fv(MODEL_MATRIX_STRING, m_ModelMatrix);
			m_Shader->SetUniformMatrix4fv(VIEW_MATRIX_STRING, m_ViewMatrix);
			m_Shader->SetUniformMatrix4fv(PROJECTION_MATRIX_STRING, m_ProjectionMatrix);
			m_VertexArray->Bind();
		}

		virtual void EndDraw() override
		{
			//...unbind...
		}

		void InitVertices(f32 w, f32 h, f32 z)
		{
			GLfloat vertices[] =
			{
				w,    0.0f, 1.0f, // Top Right
				w,    -h,	1.0f, // Bottom Right
				0.0f, -h,	1.0f, // Bottom Left
				0.0f, 0.0f, 1.0f, // Top Left 
			};

			GLuint indices[] =
			{
				0, 1, 3,
				1, 2, 3
			};

			m_VertexArray = VertexArray::Create();

			IndexBuffer* indexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));
			VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));

			BufferElement pos ("Position", VertexDataType::Float3);
			BufferLayout layout(std::vector<BufferElement> { pos });

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);
			m_VertexArray->SetIndexBuffer(indexBuffer);

			m_Shader = new OpenGLShader(GetSimpleVertexShader(), GetFragmentColorShader());
		}

		void InitVertices(f32 w, f32 h)
		{
			GLfloat vertices[] =
			{
				w,    0.0f, 1.0f,	1.0f, 1.0f,	// Top Right
				w,    -h,	1.0f,	1.0f, 0.0f,	// Bottom Right
				0.0f, -h,	1.0f,	0.0f, 0.0f,	// Bottom Left
				0.0f, 0.0f, 1.0f,	0.0f, 1.0f,	// Top Left 
			};

			GLuint indices[] =
			{
				0, 1, 3,
				1, 2, 3
			};

			m_VertexArray = VertexArray::Create();

			IndexBuffer* indexBuffer = IndexBuffer::Create(indices, ArrayCount(indices));
			VertexBuffer* vertexBuffer = VertexBuffer::Create(vertices, ArrayCount(vertices));

			BufferElement pos("Position", VertexDataType::Float3);
			BufferElement textCoord1("First texture cordinates", VertexDataType::Float2);

			BufferLayout layout(std::vector<BufferElement> {pos, textCoord1 });

			vertexBuffer->SetLayout(layout);
			m_VertexArray->AddVertexBuffer(vertexBuffer);
			m_VertexArray->SetIndexBuffer(indexBuffer);
		
			m_Shader = new OpenGLShader(GetVertexShader(), GetFragmentShader());
		}
	};

} }