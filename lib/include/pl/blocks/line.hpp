#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/line.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	/// @brief A block to create lines
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Line final : public pl::Block<API>
	{
		public:
			/// @brief A block to create lines
			/// @param instance The current instance of PresLib
			/// @param start The position of the start of the line
			/// @param end The position of the end of the line
			/// @param color The color of the line
			Line(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &start,
				const pl::math::Vec2f &end,
				pl::utils::Color color = pl::utils::undefined
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.objectColor;

				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Line(instance.getImplementation(), start, end, color);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : line's implementation's creation failed");
			}
	};

} // namespace pl::blocks
