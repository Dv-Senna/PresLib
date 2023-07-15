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
	template <pl::GraphicsApi API, class ...Args>
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
				const pl::math::Vec2f &pos1,
				const pl::math::Vec2f &pos2,
				const pl::math::Vec2f &pos3,
				Args ...args
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Triangle(instance.getImplementation(), pos1, pos2, pos3, args...);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : triangle's implementation's creation failed");
			}
	};

} // namespace pl::blocks
