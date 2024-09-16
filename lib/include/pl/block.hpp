#pragma once

#include "pl/core.hpp"
#include "pl/instance.hpp"



namespace pl {
	struct Block {
		Block() = default;
		virtual ~Block() = default;
		virtual void compile(pl::Instance *instance) = 0;
	};

	template <typename T>
	class PL_CORE BlockView {
		public:
			inline BlockView() : m_block {nullptr} {}
			inline void setBlock(pl::Block &block) {m_block = &block;}


		private:
			pl::Block *m_block;
	};

} // namespace pl
