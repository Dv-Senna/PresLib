#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../states/math.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Math final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Math(
				pl::impl::Instance *instance,
				const std::string &equation,
				const pl::math::Vec2f &pos,
				float size,
				Args ...args
			);
			virtual ~Math();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			pl::math::Vec2f m_size;
			pl::states::Math m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "math.inl"