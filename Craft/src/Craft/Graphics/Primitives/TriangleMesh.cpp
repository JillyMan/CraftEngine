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
		if (indices == nullptr || points == nullptr) {
			CR_CORE_WARN("Must have data for indices, points");
			return;
		}
		
		m_NumberOfVertices = indices->size();

		m_VertexArray = VertexArray::Create();
		//Remember: need bind here because EBO will not connect to m_VertexArray in other way.
		m_VertexArray->Bind();

		IndexBuffer* indexBuffer = IndexBuffer::Create(indices->data(), indices->size());
		VertexBuffer *pointsBuffer, *normalsBuffer, *texCoordsBuffer, *tangentsBuffer;

		pointsBuffer = VertexBuffer::Create(
			points->data(), 
			points->size(),
			BufferElement("Points", VertexDataType::Float3));

		m_VertexArray->AddVertexBuffer(pointsBuffer);
		m_VertexArray->SetIndexBuffer(indexBuffer);

		if (normals) {
			normalsBuffer = VertexBuffer::Create(
				normals->data(),
				normals->size(),
				BufferElement("Normals", VertexDataType::Float3));
			m_VertexArray->AddVertexBuffer(normalsBuffer);
		}

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

	TriangleMesh::~TriangleMesh() {
		DeleteBuffers();
	}

	void TriangleMesh::DeleteBuffers() {
		if (m_VertexArray) {
			delete m_VertexArray;
		}
	}

	void TriangleMesh::Render() {
		m_VertexArray->Bind();
		RenderCommand::DrawIndexed(m_VertexArray);
	}

}}

