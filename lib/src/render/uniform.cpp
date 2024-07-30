#include "pl/render/uniform.hpp"

#include <map>

#include <glad/gl.h>

#include "pl/assertation.hpp"



namespace pl::render {
	Uniform::Uniform(const pl::render::Uniform::CreateInfos &createInfos) :
		m_buffer {0},
		m_memoryLayout {}
	{
		static const std::map<pl::render::UniformComponentType, pl::ByteCount> typeAlignements {
			{pl::render::UniformComponentType::eFloat32, 4},
			{pl::render::UniformComponentType::eVec2f,   8},
			{pl::render::UniformComponentType::eVec3f,   16},
			{pl::render::UniformComponentType::eVec4f,   16},
			{pl::render::UniformComponentType::eMat2f,   16},
			{pl::render::UniformComponentType::eMat3f,   16},
			{pl::render::UniformComponentType::eMat4f,   16}
		};

		static const std::map<pl::render::UniformComponentType, pl::ByteCount> typeSizes {
			{pl::render::UniformComponentType::eFloat32, 4},
			{pl::render::UniformComponentType::eVec2f,   8},
			{pl::render::UniformComponentType::eVec3f,   12},
			{pl::render::UniformComponentType::eVec4f,   16},
			{pl::render::UniformComponentType::eMat2f,   32},
			{pl::render::UniformComponentType::eMat3f,   48},
			{pl::render::UniformComponentType::eMat4f,   64}
		};


		pl::ByteCount position {0};

		for (const auto &component : createInfos.components) {
			pl::render::UniformComponentMemoryLayout memoryLayout {};
			memoryLayout.type = component.type;

			pl::ByteCount alignement {typeAlignements.find(component.type)->second};
			pl::ByteCount size {typeSizes.find(component.type)->second};
			pl::ByteCount delta {position % alignement};
			if (delta != 0)
				delta = alignement - delta;

			position += delta;
			memoryLayout.start = position;

			position += size;
			memoryLayout.size = size;

			m_memoryLayout[component.name] = memoryLayout;
		}

		pl::ByteCount totalSize {position};

		glCreateBuffers(1, &m_buffer);

		glNamedBufferData(m_buffer, totalSize, nullptr, GL_STATIC_DRAW);
	}


	Uniform::~Uniform() {
		if (m_buffer != 0)
			glDeleteBuffers(1, &m_buffer);
	}


	void Uniform::write(const std::vector<pl::render::_UniformComponentValue> &components) {
		void *buffer {glMapNamedBuffer(m_buffer, GL_WRITE_ONLY)};

		for (const auto &component : components) {
			auto it {m_memoryLayout.find(component.name)};
			PL_ASSERT(it != m_memoryLayout.end(), "Can't find component '" + component.name + "' to write to the uniform");

			const auto &memoryLayout {it->second};

			switch (memoryLayout.type) {
				case pl::render::UniformComponentType::eFloat32: {
					pl::Float32 value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Float32>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eVec2f: {
					pl::Vec2f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Vec2f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eVec3f: {
					pl::Vec3f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Vec3f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eVec4f: {
					pl::Vec4f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Vec4f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eMat2f: {
					pl::Mat2f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Mat2f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eMat3f: {
					pl::Mat3f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Mat3f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}

				case pl::render::UniformComponentType::eMat4f: {
					pl::Mat4f value {reinterpret_cast<const pl::render::UniformComponentValue<pl::Mat4f>*> (&component)->value};
					memcpy(buffer + memoryLayout.start, &value, memoryLayout.size);
					break;
				}
			}
		}

		glUnmapNamedBuffer(m_buffer);
	}


	void Uniform::bind(pl::Count index) {
		glBindBufferBase(GL_UNIFORM_BUFFER, index, m_buffer);
	}


} // namespace pl::render
