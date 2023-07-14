#pragma once

#include "../../block.hpp"
#include "../../../math/vector.hpp"
#include "../../../states/image.hpp"


namespace pl::impl::SDL2_renderer::blocks
{
	class Image final : public pl::impl::Block
	{
		public:
			template <class ...Args>
			Image(
				pl::impl::Instance *instance,
				const std::string &path,
				const pl::math::Vec2f &pos,
				Args ...args
			);
			virtual ~Image();

			virtual void render();

			virtual inline void setState(const std::any &);

			virtual inline std::any getState() const noexcept;

		private:
			void s_load();
			void s_unload();

			pl::math::Vec2f m_size;
			pl::states::Image m_state;
			SDL_Texture *m_texture;
	};

} // namespace pl::impl::SDL2_renderer::blocks


#include "image.inl"