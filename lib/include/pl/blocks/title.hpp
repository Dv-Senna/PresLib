#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/title.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Title final : public pl::Block<API>
	{
		public:
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
