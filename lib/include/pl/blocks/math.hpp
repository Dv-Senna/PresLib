#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/math.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Math final : public pl::Block<API>
	{
		public:
			Math(
				pl::Instance<API> &instance,
				const std::string &equation,
				const pl::math::Vec2f &pos,
				float size,
				const pl::utils::Color &color = pl::utils::white
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Math(instance.getImplementation(), equation, pos, size, color);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : math's implementation's creation failed");
			}
	};

} // namespace pl::blocks
