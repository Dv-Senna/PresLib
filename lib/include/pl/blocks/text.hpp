#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/text.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	/// @brief A block to write text to the screen
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API, class ...Args>
	class Text final : public pl::Block<API>
	{
		public:
			Text(
				pl::Instance<API> &instance,
				const std::string &text,
				const pl::math::Vec2f &pos,
				const std::string &font,
				float size,
				Args ...args
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Text(instance.getImplementation(), text, pos, font, size, args...);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : text's implementation's creation failed");
			}
	};

} // namespace pl::blocks
