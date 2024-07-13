#pragma once

#include <vector>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/render/framebuffer.hpp"



namespace pl {
	struct Instance;

	class PL_CORE Slide {
		friend class pl::Instance;

		public:
			Slide();
			virtual ~Slide();

			void draw();
			void registerBlock(pl::Block *block);


		protected:
			void compile(pl::Instance *instance);

			std::vector<pl::Block*> m_blocks;
			pl::render::Framebuffer *m_framebuffer;
			pl::Instance *m_instance;
	};

} // namespace pl
