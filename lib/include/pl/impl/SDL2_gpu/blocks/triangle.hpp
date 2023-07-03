#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"
#include "../../../renderMethod.hpp"


namespace pl::impl::SDL2_gpu::blocks
{
	class Triangle final : public pl::impl::Block
	{
		public:
			Triangle(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &a,
				const pl::math::Vec2f &b,
				const pl::math::Vec2f &c,
				const pl::utils::Color &color,
				pl::RenderMethod method
			);
			virtual ~Triangle();

			virtual void render();

		private:
			pl::math::Vec2f m_a, m_b, m_c;
			pl::utils::Color m_color;
			pl::RenderMethod m_method;
	};

} // namespace pl::impl::SDL2_gpu::blocks
