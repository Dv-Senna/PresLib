#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/line.hpp"
#include "../impl/SDL2_gpu/blocks/line.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Line final : public pl::Block<API>
	{
		public:
			Line(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &start,
				const pl::math::Vec2f &end,
				const pl::utils::Color &color = pl::utils::white
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Line(instance.getImplementation(), start, end, color);

				else if constexpr (API == pl::GraphicsApi::SDL2_gpu)
					this->m_impl = new pl::impl::SDL2_gpu::blocks::Line(instance.getImplementation(), start, end, color);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : line's implementation's creation failed");
			}
	};

} // namespace pl::blocks
