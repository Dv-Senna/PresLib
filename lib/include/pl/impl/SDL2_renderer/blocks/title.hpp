#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../states/title.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Title final : public pl::impl::Block
	{
		public:
			Title(
				pl::impl::Instance *instance,
				const std::string &text
			);
			virtual ~Title();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			pl::math::Vec2f m_size;
			pl::states::Title m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "title.inl"