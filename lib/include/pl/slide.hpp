#pragma once

#include <vector>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/render/framebuffer.hpp"
#include "pl/render/renderer.hpp"



namespace pl {
	struct Instance;

	class PL_CORE Slide {
		friend class pl::Instance;

		public:
			struct CreateInfos {
				pl::Vec2i viewportSize {-1, -1};
			};

			Slide(const pl::Slide::CreateInfos &createInfos);
			virtual ~Slide();

			virtual void update();
			void draw();
			void registerBlock(pl::Block *block);

			inline const pl::render::Framebuffer &getFramebuffer() const noexcept {return *m_framebuffer;}
			inline const pl::Vec2i &getViewportSize() const noexcept {return m_viewportSize;}
			inline const pl::Vec2i &getOriginalViewportSize() const noexcept {return m_originalViewportSize;}


		protected:
			void compile(pl::Instance *instance);
			void resize(const pl::Vec2i &size);

			std::vector<pl::Block*> m_blocks;
			pl::render::Framebuffer *m_framebufferMSAA;
			pl::render::Framebuffer *m_framebuffer;
			pl::render::Renderer m_renderer;
			pl::Vec2i m_viewportSize;
			pl::Vec2i m_originalViewportSize;
			pl::Instance *m_instance;
	};

} // namespace pl
