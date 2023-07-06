#pragma once

#include <iostream>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/rectangle.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"
#include "../renderMethod.hpp"


namespace pl::blocks
{
	/// @brief A block to create rectangles
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Rectangle final : public pl::Block<API>
	{
		public:
			/// @brief A block to create rectangles
			/// @param instance The current instance of PresLib
			/// @param pos The top-left corner of the rectangle
			/// @param size The size of the rectangle
			/// @param color The color of the rectangle
			/// @param method `pl::RenderMethod::fill` for filled rectangle, `pl::RenderMethod::border` for outlined rectangle
			Rectangle(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &pos,
				const pl::math::Vec2f &size,
				pl::utils::Color color = pl::utils::undefined,
				pl::RenderMethod method = pl::RenderMethod::fill
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.objectColor;

				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Rectangle(instance.getImplementation(), pos, size, color, method);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : rectangle's implementation's creation failed");
			}
	};

} // namespace pl::blocks
