#include "crpch.h"

#include "TriangleMesh.h"
#include "Craft/Graphics/RenderCommand.h"

namespace Craft { namespace Graphics {

	void TriangleMesh::InitBuffers(
		std::vector<u32>* indices, 
		std::vector<f32>* points, 
		std::vector<f32>* normals, 
		std::vector<f32>* texCoords, 
		std::vector<f32>* tangents
	) {
		if (indices == nullptr || points == nullptr || normals == nullptr) {
			CR_CORE_WARN("Must have data for indices, points, and normals");
			return;
		}
		
		m_NumberOfVertices = indices->size();

		m_VertexArray = VertexArray::Create();
		IndexBuffer* indexBuffer = IndexBuffer::Create(indices->data(), indices->size());
		VertexBuffer *pointsBuffer, *normalsBuffer, *texCoordsBuffer, *tangentsBuffer;

		pointsBuffer = VertexBuffer::Create(
			points->data(), 
			points->size(),
			BufferElement("Points", VertexDataType::Float3));

		normalsBuffer = VertexBuffer::Create(
			normals->data(),
			normals->size(),
			BufferElement("Normals", VertexDataType::Float3));

		m_VertexArray->AddVertexBuffer(pointsBuffer);
		m_VertexArray->AddVertexBuffer(normalsBuffer);
		
		if (texCoords) {
			texCoordsBuffer = VertexBuffer::Create(
				texCoords->data(),
				texCoords->size(),
				BufferElement("Texture coords", VertexDataType::Float2));
			m_VertexArray->AddVertexBuffer(texCoordsBuffer);
		}

		if (tangents) {
			//.... init tangents buffer
		}
	}

	void TriangleMesh::DeleteBuffers() {
		delete m_VertexArray;
	}

	void TriangleMesh::Render() {
		RenderCommand::DrawIndexed(m_VertexArray);
	}

}}

