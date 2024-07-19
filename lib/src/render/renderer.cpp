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
		std::vector<pl::Byte> vertices {};
		for (const auto &block : group.blocks)
			vertices.insert(vertices.end(), block->getState().vertices.begin(), block->getState().vertices.end());

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
			&& *group.vertexLayout == *descriptor.vertexLayout;
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
			m_renderGroups.push_back(group);
		}

		for (auto &group : m_renderGroups)
			generateGroupVertices(m_instance, group);
	}


	void Renderer::draw(pl::render::Framebuffer *framebuffer) {
		if (framebuffer != nullptr)
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, framebuffer->getFramebuffer());
		else
			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);


		pl::render::Pipeline *oldPipeline {nullptr};
		for (const auto &group : m_renderGroups) {
			group.vertexLayout->linkBuffer(group.vertexBuffer);

			group.vertexLayout->use();
			group.pipeline->useFrom(oldPipeline);

			glDrawArrays(GL_TRIANGLES, 0, group.vertexBuffer->getSize() / group.vertexLayout->getStride());

			oldPipeline = group.pipeline;
		}
	}


} // namespace pl::render
