#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/text.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Text final : public pl::Block<API>
	{
		public:
			Text(
				pl::Instance<API> &instance,
				const std::string &text,
				const pl::math::Vec2f &pos,
				const std::string &font,
				float size,
				pl::utils::Color color = pl::utils::undefined
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.textColor;

				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Text(instance.getImplementation(), text, pos, font, size, color);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : text's implementation's creation failed");
			}
	};

} // namespace pl::blocks
