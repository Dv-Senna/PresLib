#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/ellipse.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	/// @brief A block to create ellipses and circles
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Ellipse final : public pl::Block<API>
	{
		public:
			/// @brief A block to create ellipses and circle
			/// @param instance The current instance of PresLib
			/// @param center The position of the center of the ellipse
			/// @param radius The largest radius of the ellipse
			/// @param excentricity `0.0f` for circle, `< 1.0f` for ellipse. Bigger values mean less 'round' ellipses
			/// @param angle The rotation angle (doesn't work for the moment, here only for futur APIs)
			/// @param color The color of the ellipse
			/// @param method `pl::RenderMethod::fill` for filled ellipse, `pl::RenderMethod::border` for outlined ellipse
			Ellipse(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &center,
				float radius,
				float excentricity = 0.0f,
				float angle = 0.0f,
				pl::utils::Color color = pl::utils::undefined,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.objectColor;

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
