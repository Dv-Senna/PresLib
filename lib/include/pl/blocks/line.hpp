#pragma once

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/line.hpp"
#include "../math/vector.hpp"
#include "../utils/color.hpp"


namespace pl::blocks
{
	/// @brief A block to create lines
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API, class ...Args>
	class Line final : public pl::Block<API>
	{
		public:
			Line(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &start,
				const pl::math::Vec2f &end,
				Args ...args
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Line(instance.getImplementation(), start, end, args...);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : line's implementation's creation failed");
			}
	};

} // namespace pl::blocks
