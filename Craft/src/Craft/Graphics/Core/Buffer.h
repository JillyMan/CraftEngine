#pragma once

namespace Craft { namespace Graphics {

	enum class VertexDataType
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Double,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		UnsignedInt,
		Bool
	};

	static u32 GetDataTypeSize(VertexDataType DataType)
	{
		switch (DataType)
		{
		case VertexDataType::Double:		return 8;
		case VertexDataType::Bool:			return 1;

		case VertexDataType::Int:			return 4;
		case VertexDataType::Int2:			return 4 * 2;
		case VertexDataType::Int3:			return 4 * 3;
		case VertexDataType::Int4:			return 4 * 4;
		case VertexDataType::UnsignedInt:	return 4;

		case VertexDataType::Float:			return 4;
		case VertexDataType::Float2:		return 4 * 2;
		case VertexDataType::Float3:		return 4 * 3;
		case VertexDataType::Float4:		return 4 * 4;

		case VertexDataType::Mat3:		return 4 * (3 * 3);
		case VertexDataType::Mat4:		return 4 * (4 * 4);
		};

		CR_ASSERT(false, "Invalid DataType.");
		return 0;
	}

	struct BufferElement
	{
		bool Normalized;
		VertexDataType DataType;
		s32 Size;
		u32 Offset;
		String Name;

		BufferElement() = default;

		BufferElement(const char* name, VertexDataType dataType, bool normalized = false) :
			Name(name),
			Size(GetDataTypeSize(dataType)),
			DataType(dataType),
			Normalized(normalized),
			Offset(0)
		{
		}

		u32 GetComponentCount() const
		{
			switch (DataType)
			{
			case VertexDataType::Double:		return 1;
			case VertexDataType::Bool:			return 1;

			case VertexDataType::Int:			return 4;
			case VertexDataType::Int2:			return 2;
			case VertexDataType::Int3:			return 3;
			case VertexDataType::Int4:			return 4;
			case VertexDataType::UnsignedInt:	return 1;

			case VertexDataType::Float:			return 1;
			case VertexDataType::Float2:		return 2;
			case VertexDataType::Float3:		return 3;
			case VertexDataType::Float4:		return 4;

			case VertexDataType::Mat3:		return (3 * 3);
			case VertexDataType::Mat4:		return (4 * 4);
			};

			CR_ASSERT(false, "i'ts imposible");
			return 0;
		}
	};

	struct BufferLayout
	{
	private:
		u32 m_Stride;
		std::vector<BufferElement> m_Elements;

		void CalculateStrideAndOffset()
		{
			m_Stride = 0;

			for (auto& element : m_Elements)
			{
				element.Offset = m_Stride;
				m_Stride += element.Size;
			}
		}

	public:
		BufferLayout() : m_Stride(0) {}

		//initilize_ilst need use here
		BufferLayout(std::vector<BufferElement>& elements) :
			m_Elements(elements),
			m_Stride(0)
		{
			CalculateStrideAndOffset();
		}

		void SetElements(std::vector<BufferElement>& elements)
		{
			m_Elements = elements;
		}

		u32 GetStride() const { return m_Stride; }

		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }
	};

	class VertexBuffer
	{
	public:
		virtual ~VertexBuffer() { }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetCount() = 0;

		virtual void SetLayout(BufferLayout& attribute) = 0;
		virtual const BufferLayout& GetLayout() = 0;

		static VertexBuffer* Create(f32* vertices, s32 size);
		static VertexBuffer* Create(f32* values, s32 size, BufferElement& element);
	};

	class IndexBuffer
	{
	public:
		virtual ~IndexBuffer() { }

		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual u32 GetCount() = 0;

		static IndexBuffer* Create(u32* indices, s32 count);
	};
}}