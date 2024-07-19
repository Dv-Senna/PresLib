#pragma once

#include <vector>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/render/buffer.hpp"
#include "pl/render/framebuffer.hpp"
#include "pl/render/pipeline.hpp"
#include "pl/render/vertexLayout.hpp"
#include "pl/types.hpp"



namespace pl {
	struct Instance;
} // namespace pl


namespace pl::render {
	struct RenderGroup {
		pl::render::Buffer *vertexBuffer;
		pl::render::Pipeline *pipeline;
		pl::render::VertexLayout *vertexLayout;
		std::vector<pl::Block*> blocks;
	};

	class Renderer {
		public:
			Renderer();
			~Renderer();

			void compile(pl::Instance *instance, const std::vector<pl::Block*> &blocks);
			void draw(pl::render::Framebuffer *framebuffer);

		private:
			pl::Instance *m_instance;
			std::vector<pl::render::RenderGroup> m_renderGroups;
	};

} // namespace pl::render
