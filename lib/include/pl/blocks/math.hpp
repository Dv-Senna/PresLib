#pragma once

#include <iostream>
#include <string>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/math.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	/// @brief A block to render LaTeX equations
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Math final : public pl::Block<API>
	{
		public:
			/// @brief A block to render LaTeX equations
			/// @param instance The current instance of PresLib
			/// @param equation The equation in LaTeX format
			/// @param pos The position of the equation (note : the equation will be offset to the right because of unwanted margin in the pdf)
			/// @param size The size of the font in pt
			/// @param color The color of the equation
			/// @warning Replace `\ \ ` by `\ ` in your equation !
			Math(
				pl::Instance<API> &instance,
				const std::string &equation,
				const pl::math::Vec2f &pos,
				float size,
				pl::utils::Color color = pl::utils::undefined
			) : pl::Block<API> ()
			{
				if (color == pl::utils::undefined)
					color = instance.getTheme().style.textColor;

				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Math(instance.getImplementation(), equation, pos, size, color);
				

				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : math's implementation's creation failed");
			}
	};

} // namespace pl::blocks
