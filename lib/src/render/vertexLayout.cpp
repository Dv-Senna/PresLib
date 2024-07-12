#include "pl/render/vertexLayout.hpp"

#include <map>

#include <glad/gl.h>



namespace pl::render {
	VertexLayout::VertexLayout(const pl::render::VertexLayout::CreateInfos &createInfos) :
		m_binding {createInfos.binding},
		m_components {createInfos.components},
		m_rate {createInfos.rate},
		m_hash {},
		m_vao {0},
		m_stride {0}
	{
		static const std::map<pl::render::VertexComponentType, GLenum> typeMap {
			{pl::render::VertexComponentType::eFloat32, GL_FLOAT},
			{pl::render::VertexComponentType::eInt32,   GL_INT},
			{pl::render::VertexComponentType::eUint32,  GL_UNSIGNED_INT}
		};

		pl::ByteCount componentByteSize {sizeof(pl::render::VertexComponentLayout) * sizeof(m_components.size())};
		std::vector<pl::Byte> hashData {};
		hashData.resize(sizeof(pl::Uint32) + componentByteSize);
		hashData[0] = m_binding;
		memcpy(hashData.data() + 1, m_components.data(), componentByteSize);
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


} // namespace pl::render
