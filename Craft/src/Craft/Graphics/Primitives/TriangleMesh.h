#pragma once

#include "Drawable.h"
#include <Craft/Graphics/Core/Buffer.h>
#include <Craft/Graphics/Core/VertexArray.h>

namespace Craft { namespace Graphics {

	class TriangleMesh : public Drawable {
	private:
		u32 m_NumberOfVertices;
		VertexArray* m_VertexArray;
		//std::vector<VertexBuffer*> m_Buffers;

	protected:

		virtual void InitBuffers(
			std::vector<u32>* indices,
			std::vector<f32>* points,
			std::vector<f32>* normals,
			std::vector<f32>* texCoords = nullptr,
			std::vector<f32>* tangents = nullptr
		);

		virtual void DeleteBuffers();

	public: 
		virtual ~TriangleMesh();
		virtual void Render();

		VertexArray* GetVertexArray() const { return m_VertexArray; }
	};

} }
