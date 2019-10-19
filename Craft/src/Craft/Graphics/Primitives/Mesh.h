#pragma once

#include <Craft/Graphics/VertexArray.h>

namespace Craft { namespace Graphics {

	class Mesh
	{
	private:
		VertexArray* m_VertexArray;

	public:
		Mesh(VertexBuffer* vertexBuffer, IndexBuffer* indexBuffer)
		{
		}

		~Mesh() { delete m_VertexArray; }

		inline const VertexArray* GetVertexArray() const { return m_VertexArray; }

		static Mesh* GenerateSquadWithTextureCoord(f32 x, f32 y, f32 w, f32 h)
		{
		}

		static Mesh* GenerateCubeWithTextureCoord()
		{
		}
	};
} }