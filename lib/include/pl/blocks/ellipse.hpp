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
	template <pl::GraphicsApi API, class ...Args>
	class Ellipse final : public pl::Block<API>
	{
		public:
			Ellipse(
				pl::Instance<API> &instance,
				const pl::math::Vec2f &center,
				float radius,
				Args ...args
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Ellipse(
						instance.getImplementation(), center, radius, args...
					);


				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : ellipse's implementation's creation failed");
			}
	};

} // namespace pl::blocks
