#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../utils/color.hpp"
#include "../../../renderMethod.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Rectangle final : public pl::impl::Block
	{
		public:
			Rectangle(
				pl::impl::Instance *instance,
				const pl::math::Vec2f &pos,
				const pl::math::Vec2f &size,
				const pl::utils::Color &color,
				pl::RenderMethod method
			);
			virtual ~Rectangle();

			virtual void render();

		private:
			pl::math::Vec2f m_pos, m_size;
			pl::utils::Color m_color;
			pl::RenderMethod m_method;
	};

} // namespace pl::impl::SDL2_renderer::blocks
