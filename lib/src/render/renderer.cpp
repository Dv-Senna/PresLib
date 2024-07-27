#include "pl/render/renderer.hpp"

#include <glad/gl.h>

#include "pl/instance.hpp"



namespace pl::render {
	Renderer::Renderer() :
		m_instance {nullptr},
		m_renderGroups {}
	{

	}


	Renderer::~Renderer() {
		if (m_instance == nullptr)
			return;

		for (auto &group : m_renderGroups) {
			if (group.vertexBuffer != nullptr)
				m_instance->freeObject(group.vertexBuffer);
		}
	}


	void generateGroupVertices(pl::Instance *instance, pl::render::RenderGroup &group) {
		static const std::map<VertexComponentType, pl::ByteCount> typeSizeMap {
			{pl::render::VertexComponentType::eFloat32, sizeof(pl::Float32)},
			{pl::render::VertexComponentType::eInt32,   sizeof(pl::Int32)},
			{pl::render::VertexComponentType::eUint32,  sizeof(pl::Uint32)}
		};

		std::vector<pl::Byte> vertices {};
		for (const auto &block : group.blocks) {
			auto blockVertices {block->getState().vertices};

			pl::ByteCount stride {block->getState().renderDescriptor.vertexLayout->getStride()};
			pl::Count verticesCount {blockVertices.size() / stride};
			pl::ByteCount offset {0};

			for (const auto &component : block->getState().renderDescriptor.vertexLayout->getComponents()) {
				pl::ByteCount oldOffset {offset};
				pl::ByteCount typeSize {typeSizeMap.find(component.type)->second};
				offset += typeSize;

				if (!component.isPosition)
					continue;

				PL_ASSERT(component.type == pl::render::VertexComponentType::eFloat32, "Position vertex component's type must be float32");

				pl::Float32 rotsin {sinf(block->getState().rotation.x)};
				pl::Float32 rotcos {cosf(block->getState().rotation.x)};
				pl::Vec2f rotationCenter {block->getState().rotation.y, block->getState().rotation.z};
				rotationCenter *= block->getState().zoom;

				pl::Mat3f rotationMatrix {
					rotcos, -rotsin, 0.f,
					rotsin, rotcos,  0.f,
					0.f,    0.f,     1.f
				};

				pl::Mat3f translationMatrix {
					1.f, 0.f, block->getState().position.x,
					0.f, 1.f, block->getState().position.y,
					0.f, 0.f, 1.f
				};

				pl::Mat3f zoomMatrix {
					block->getState().zoom.x, 0.f,                      0.f,
					0.f,                      block->getState().zoom.y, 0.f,
					0.f,                      0.f,                      1.f
				};

				pl::Mat3f rotationCenterMatrix {
					1.f, 0.f, -rotationCenter.x,
					0.f, 1.f, -rotationCenter.y,
					0.f, 0.f, 1.f
				};

				pl::Mat3f inverseRotationCenterMatrix {
					1.f, 0.f, rotationCenter.x,
					0.f, 1.f, rotationCenter.y,
					0.f, 0.f, 1.f
				};

				pl::Mat3f transformationMatrix {
					translationMatrix * inverseRotationCenterMatrix * rotationMatrix * rotationCenterMatrix * zoomMatrix
				};



				for (pl::Count i {0}; i < verticesCount; ++i) {
					PL_ASSERT(component.dimension == 2, "Position vertex component's dimension must be 2");

					pl::ByteCount dataPosition {oldOffset + stride * i};
					pl::Float32 *x {reinterpret_cast<pl::Float32*> (blockVertices.data() + dataPosition)};
					pl::Float32 *y {reinterpret_cast<pl::Float32*> (blockVertices.data() + dataPosition + sizeof(pl::Float32))};

					pl::Vec3f position {*x, *y, 1.f};
					position = transformationMatrix * position;

					*x = position.x;
					*y = position.y;
				}
			}

			vertices.insert(vertices.end(), blockVertices.begin(), blockVertices.end());
		}

		bool build {true};

		if (group.vertexBuffer != nullptr) {
			if (group.vertexBuffer->getSize() != vertices.size() * sizeof(pl::Byte))
				instance->freeObject(group.vertexBuffer);
			else
				build = false;
		}

		if (build) {
			pl::render::Buffer::CreateInfos createInfos {};
			createInfos.usage = pl::render::BufferUsage::eDynamic;
			createInfos.type = pl::render::BufferType::eVertex;
			createInfos.size = vertices.size() * sizeof(pl::Byte);
			group.vertexBuffer = instance->allocateObject<pl::render::Buffer> (createInfos);
		}

		group.vertexBuffer->write(0, vertices.size() * sizeof(pl::Byte), vertices.data());
	}


	bool isSame(const pl::render::RenderGroup &group, const pl::render::Descriptor &descriptor) {
		return *group.pipeline == *descriptor.pipeline
			&& *group.vertexLayout == *descriptor.vertexLayout
			&& group.textures == descriptor.textures;
	}


	void Renderer::compile(pl::Instance *instance, const std::vector<pl::Block*> &blocks) {
		m_instance = instance;

		for (auto &block : blocks) {
			bool found {false};

			for (auto &group : m_renderGroups) {
				if (!isSame(group, block->getState().renderDescriptor))
					continue;
				
				found = true;
				group.blocks.push_back(block);
				break;
			}

			if (found)
				continue;

			pl::render::RenderGroup group {};
			group.blocks = {block};
			group.pipeline = block->getState().renderDescriptor.pipeline;
			group.vertexLayout = block->getState().renderDescriptor.vertexLayout;
			group.vertexBuffer = nullptr;
			group.textures = block->getState().renderDescriptor.textures;
			m_renderGroups.push_back(group);
		}

		for (auto &group : m_renderGroups)
			generateGroupVertices(m_instance, group);
	}


	void Renderer::draw(pl::render::Framebuffer *framebuffer) {
		if (framebuffer != nullptr) {
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->getFramebuffer());
			glViewport(0, 0, framebuffer->getSize().x, framebuffer->getSize().y);
		}

		else
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


		glClearColor(0.1f, 0.1f, 0.1f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);

		pl::render::Pipeline *oldPipeline {nullptr};
		for (const auto &group : m_renderGroups) {
			group.vertexLayout->linkBuffer(group.vertexBuffer);

			group.vertexLayout->use();
			group.pipeline->useFrom(oldPipeline);

			for (const auto &texture : group.textures)
				glBindTextureUnit(texture.first, texture.second->getTexture());

			glDrawArrays(GL_TRIANGLES, 0, group.vertexBuffer->getSize() / group.vertexLayout->getStride());

			for (const auto &texture : group.textures)
				glBindTextureUnit(texture.first, 0);

			oldPipeline = group.pipeline;
		}
	}


} // namespace pl::render
