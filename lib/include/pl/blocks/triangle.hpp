#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/triangle.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	/// @brief A block to create triangles
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Triangle final : public pl::Block<API>
	{
		public:
			/// @brief A block to create triangle
			/// @param instance The current instance of PresLib
			/// @param a The first corner of the triangle
			/// @param b The second corner of the triangle
			/// @param c The third corner of the triangle
			/// @param color The color of the triangle
			/// @param method `pl::RenderMethod::fill` for filled triangle, `pl::RenderMethod::border` for outlined triangle
			Triangle(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &a,
				const pl::math::Vec2f &b,
				const pl::math::Vec2f &c,
				pl::utils::Color color = pl::utils::undefined,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.objectColor;

				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Triangle(instance.getImplementation(), a, b, c, color, method);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : triangle's implementation's creation failed");
			}
	};

} // namespace pl::blocks
