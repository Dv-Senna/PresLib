#pragma once

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::render {
	enum class FramebufferColorFormat {
		eRGB8,
		eRGBA8,
		eRGB32f,
		eRGBA32f,
		eR11fG11fB10f,
	};

	class PL_CORE Framebuffer final {
		public:
			struct CreateInfos {
				pl::Vec2i size;
				bool hasDepth;
				pl::render::FramebufferColorFormat colorFormat;
			};

			Framebuffer(const pl::render::Framebuffer::CreateInfos &infos);
			~Framebuffer();

			void resize(const pl::Vec2i &size);
			void clear(const pl::Vec3f &color);

		private:
			void m_create(bool depthBuffer);
			void m_destroy();

			pl::Uint32 m_colorFormat;
			pl::Vec2i m_size;
			pl::Uint32 m_colorTexture;
			pl::Uint32 m_depthRenderbuffer;
			pl::Uint32 m_framebuffer;
	};

} // namespace pl::render
