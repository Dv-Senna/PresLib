#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/ellipse.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	template <pl::GraphicsApi API>
	class Ellipse final : public pl::Block<API>
	{
		public:
			Ellipse(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &center,
				float radius,
				float excentricity = 0.0f,
				float angle = 0.0f,
				const pl::utils::Color &color = pl::utils::white,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Ellipse(
						instance.getImplementation(),
						center, radius, excentricity, angle, color, method
					);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : ellipse's implementation's creation failed");
			}
	};

} // namespace pl::blocks
