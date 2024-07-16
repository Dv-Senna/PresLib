#include "pl/render/vertexLayout.hpp"

#include <map>

#include <glad/gl.h>

#include "pl/assertation.hpp"



namespace pl::render {
	VertexLayout::VertexLayout(const pl::render::VertexLayout::CreateInfos &createInfos) :
		m_binding {createInfos.binding},
		m_components {createInfos.components},
		m_rate {createInfos.rate},
		m_hash {},
		m_vao {0},
		m_stride {0},
		m_linkedBuffer {nullptr}
	{
		static const std::map<pl::render::VertexComponentType, GLenum> typeMap {
			{pl::render::VertexComponentType::eFloat32, GL_FLOAT},
			{pl::render::VertexComponentType::eInt32,   GL_INT},
			{pl::render::VertexComponentType::eUint32,  GL_UNSIGNED_INT}
		};

		pl::ByteCount componentByteSize {sizeof(pl::render::VertexComponentLayout) * m_components.size()};
		std::vector<pl::Byte> hashData {};
		hashData.resize(sizeof(pl::Uint32) + componentByteSize + sizeof(pl::render::VertexRate));
		*reinterpret_cast<pl::Uint32*> (hashData.data()) = m_binding;
		memcpy(hashData.data() + sizeof(pl::Uint32), m_components.data(), componentByteSize);
		memcpy(hashData.data() + sizeof(pl::Uint32) + componentByteSize, &m_rate, sizeof(pl::render::VertexRate));
		m_hash = pl::utils::hash(hashData);

		glCreateVertexArrays(1, &m_vao);

		for (const auto &component : m_components) {
			glVertexArrayAttribFormat(
				m_vao,
				component.location,
				component.dimension,
				typeMap.find(component.type)->second,
				GL_FALSE,
				m_stride
			);
			glEnableVertexArrayAttrib(m_vao, component.location);
			glVertexArrayAttribBinding(m_vao, component.location, m_binding);
			m_stride += component.dimension * 4;
		}
	}


	VertexLayout::~VertexLayout() {
		if (m_vao != 0)
			glDeleteVertexArrays(1, &m_vao);
	}


	bool VertexLayout::operator==(const pl::render::VertexLayout &layout) {
		return m_hash == layout.m_hash;
	}


	void VertexLayout::linkBuffer(const pl::render::Buffer *buffer) {
		PL_ASSERT(this->isValid(), "Can't link buffer to invalid vertex layout");
		if (m_linkedBuffer == buffer)
			return;

		PL_ASSERT(buffer->isValid(), "Can't link invalid buffer");
		PL_ASSERT(buffer->getType() == pl::render::BufferType::eVertex, "Can't link buffer of wrong type");

		m_linkedBuffer = buffer;
		glVertexArrayVertexBuffer(m_vao, m_binding, buffer->getBuffer(), 0, m_stride);
	}


} // namespace pl::render
