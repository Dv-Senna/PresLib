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


	/// @brief A class to handle slide
	class Slide final
	{
		public:
			/// @brief A class to handle slide
			/// @tparam API The graphics api used
			/// @param instance The current instance of PresLib
			/// @param flags Some pl::SlideFlag separated by `|`
			/// @note The constructor register himself directly to the instance. You mustn't call instance.addSlide(...)
			template <pl::GraphicsApi API>
			Slide(pl::Instance<API> &instance, pl::SlideFlags flags = pl::SlideFlag::noFlag);
			~Slide() = default;

			/// @brief Render the content of the slide
			void render();

			/// @brief Register a new block into the slide. Block's drawing order is the order of registration
			/// @tparam API The graphics api used
			/// @param block The block to register
			template <pl::GraphicsApi API>
			void addBlock(pl::Block<API> *block);

			inline pl::SlideFlags getFlags() const noexcept;

		
		private:
			std::list<pl::impl::Block *> m_blocks;
			pl::SlideFlags m_flags;
	};

} // namespace pl


#include "slide.inl"