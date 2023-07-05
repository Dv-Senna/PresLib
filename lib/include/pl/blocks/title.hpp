#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/title.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	/// @brief A block to add title to a slide
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Title final : public pl::Block<API>
	{
		public:
			/// @brief A block to add title to a slide
			/// @param instance The current instance of PresLib
			/// @param text The text used as title of the slide
			/// @param slide The slide which has the title
			Title(
				pl::Instance<API> &instance,
				const std::string &text,
				pl::Slide &slide
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Title(instance.getImplementation(), text);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : title's implementation's creation failed");

				slide.addBlock(this);
			}
	};

} // namespace pl::blocks
