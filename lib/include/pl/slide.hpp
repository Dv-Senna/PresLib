#pragma once

#include <vector>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/render/framebuffer.hpp"
#include "pl/render/renderer.hpp"



namespace pl {
	struct Instance;

	class PL_CORE Slide {
		friend class pl::Instance;

		public:
			Slide();
			virtual ~Slide();

			virtual void update();
			void draw();
			void registerBlock(pl::Block *block);


		protected:
			void compile(pl::Instance *instance);

			std::vector<pl::Block*> m_blocks;
			pl::render::Framebuffer *m_framebuffer;
			pl::render::Renderer m_renderer;
			pl::Instance *m_instance;
	};

} // namespace pl
