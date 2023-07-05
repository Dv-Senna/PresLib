#pragma once

#include <list>

#include "graphicsApi.inl"


namespace pl
{
	template <pl::GraphicsApi API>
	class Instance;

	template <pl::GraphicsApi API>
	class Block;

	namespace impl
	{
		class Block;
	}


	using SlideFlags = uint8_t;

	namespace SlideFlag
	{
		inline pl::SlideFlags noFlag {0};
		inline pl::SlideFlags noBackground {0b00000001};
		inline pl::SlideFlags noForeground {0b00000010};
	};


	class Slide final
	{
		public:
			template <pl::GraphicsApi API>
			Slide(pl::Instance<API> &instance, pl::SlideFlags flags = pl::SlideFlag::noFlag);
			~Slide() = default;

			void render();

			template <pl::GraphicsApi API>
			void addBlock(pl::Block<API> *block);

			inline pl::SlideFlags getFlags() const noexcept;

		
		private:
			std::list<pl::impl::Block *> m_blocks;
			pl::SlideFlags m_flags;
	};

} // namespace pl


#include "slide.inl"