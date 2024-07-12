#include "pl/render/buffer.hpp"

#include <map>

#include <glad/gl.h>

#include "pl/assertation.hpp"



namespace pl::render {
	Buffer::Buffer(const pl::render::Buffer::CreateInfos &createInfos) :
		m_type {createInfos.type},
		m_usage {createInfos.usage},
		m_size {createInfos.size},
		m_buffer {0}
	{
		/*static const std::map<pl::render::BufferType, GLenum> typeMap {
			{pl::render::BufferType::eVertex, GL_ARRAY_BUFFER}
		};*/

		static const std::map<std::tuple<pl::render::BufferType, pl::render::BufferUsage>, GLenum> usageMap {
			{{pl::render::BufferType::eVertex, pl::render::BufferUsage::eStatic}, GL_STATIC_DRAW},
			{{pl::render::BufferType::eVertex, pl::render::BufferUsage::eDynamic}, GL_DYNAMIC_DRAW}
		};

		glCreateBuffers(1, &m_buffer);
		glNamedBufferData(m_buffer, m_size, nullptr, usageMap.find({m_type, m_usage})->second);
	}


	Buffer::~Buffer() {
		if (m_buffer != 0)
			glDeleteBuffers(1, &m_buffer);
	}


	void Buffer::write(pl::ByteCount offset, pl::ByteCount size, pl::Byte *data) {
		PL_ASSERT(this->isValid(), "Can't write undefined buffer");
		glNamedBufferSubData(m_buffer, offset, size, data);
	}


} // namespace pl::render
