#pragma once

#include "pl/core.hpp"
#include "pl/render/texture.hpp"
#include "pl/types.hpp"



namespace pl::render {
	class PL_CORE Framebuffer final {
		public:
			struct CreateInfos {
				pl::render::TextureFormat colorFormat;
				pl::Vec2i size;
				bool hasDepth;
				bool multisampled;
			};

			Framebuffer(const pl::render::Framebuffer::CreateInfos &infos);
			~Framebuffer();

			void resize(const pl::Vec2i &size);
			void clear(const pl::Vec3f &color);

			void resolveMSAA(const pl::render::Framebuffer &framebuffer);

			inline const pl::Uint32 &getFramebuffer() const noexcept {return m_framebuffer;}

		private:
			void m_create(bool depthBuffer);
			void m_destroy();

			pl::render::TextureFormat m_colorFormat;
			pl::Vec2i m_size;
			pl::render::Texture *m_colorTexture;
			pl::Uint32 m_depthRenderbuffer;
			pl::Uint32 m_framebuffer;
			bool m_multisampled;
	};

} // namespace pl::render
