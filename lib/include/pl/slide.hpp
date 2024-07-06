#pragma once

#include <vector>

#include "pl/block.hpp"
#include "pl/core.hpp"



namespace pl {
	class PL_CORE Slide {
		public:
			Slide();
			virtual ~Slide();

			void draw();
			void registerBlock(pl::Block *block);


		protected:
			std::vector<pl::Block*> m_blocks;
	};

} // namespace pl
