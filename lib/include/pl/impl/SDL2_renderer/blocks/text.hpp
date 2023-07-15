#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../states/text.hpp"
#include "../../../utils/color.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Text final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Text(
				pl::impl::Instance *instance,
				const std::string &text,
				const pl::math::Vec2f &pos,
				const std::string &font,
				float size,
				Args ...args
			);
			virtual ~Text();

			virtual void render();

			virtual inline void setState(const std::any &state);

			virtual inline std::any getState() const noexcept;

		private:
			void m_load();
			void m_unload();

			pl::math::Vec2f m_size;
			pl::states::Text m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "text.inl"