#include "pl/render/framebuffer.hpp"

#include <map>
#include <stdexcept>

#include <glad/gl.h>

#include "pl/assertation.hpp"



namespace pl::render {
	Framebuffer::Framebuffer(const pl::render::Framebuffer::CreateInfos &infos) :
		m_colorFormat {infos.colorFormat},
		m_size {infos.size},
		m_colorTexture {nullptr},
		m_depthRenderbuffer {0},
		m_framebuffer {0},
		m_multisampled {infos.multisampled}
	{
		this->m_create(infos.hasDepth);
	}


	Framebuffer::~Framebuffer() {
		this->m_destroy();
	}


	void Framebuffer::resize(const pl::Vec2i &size) {
		bool hasDepth {m_depthRenderbuffer != 0};
		this->m_destroy();
		m_size = size;
		this->m_create(hasDepth);
	}


	void Framebuffer::clear(const pl::Vec3f &color) {
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_framebuffer);
		glClearColor(color.r, color.g, color.b, 1.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}


	void Framebuffer::resolveMSAA(const pl::render::Framebuffer &framebuffer) {
		PL_ASSERT(framebuffer.m_multisampled, "Can't resolve non-multisample framebuffer");
		PL_ASSERT(!m_multisampled, "Can't resolve multisample framebuffer into a multisample framebuffer");
		PL_ASSERT(m_size == framebuffer.m_size, "Can't resolve multisample framebuffer into framebuffer of different size");

		glBlitNamedFramebuffer(
			framebuffer.m_framebuffer,
			m_framebuffer,
			0, 0, m_size.x, m_size.y,
			0, 0, m_size.x, m_size.y,
			GL_COLOR_BUFFER_BIT, GL_NEAREST
		);
	}


	void Framebuffer::m_create(bool depthBuffer) {
		pl::render::Texture::CreateInfos textureCreateInfos {};
		textureCreateInfos.data = nullptr;
		textureCreateInfos.format = m_colorFormat;
		textureCreateInfos.mipmapLevelCount = 1;
		textureCreateInfos.multisample = m_multisampled;
		textureCreateInfos.size = m_size;
		m_colorTexture = new pl::render::Texture(textureCreateInfos);

		glCreateFramebuffers(1, &m_framebuffer);
		glNamedFramebufferTexture(m_framebuffer, GL_COLOR_ATTACHMENT0, m_colorTexture->getTexture(), 0);

		if (depthBuffer) {
			glCreateRenderbuffers(1, &m_depthRenderbuffer);
			glNamedRenderbufferStorage(m_depthRenderbuffer, GL_DEPTH24_STENCIL8, m_size.x, m_size.y);
			glNamedFramebufferRenderbuffer(m_framebuffer, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_depthRenderbuffer);
		}

		if (glCheckNamedFramebufferStatus(m_framebuffer, GL_DRAW_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			throw std::runtime_error("Created framebuffer is not complete");
	}


	void Framebuffer::m_destroy() {
		if (m_framebuffer != 0)
			glDeleteFramebuffers(1, &m_framebuffer);
		if (m_depthRenderbuffer != 0)
			glDeleteRenderbuffers(1, &m_depthRenderbuffer);
		if (m_colorTexture != nullptr)
			delete m_colorTexture;

		m_colorTexture = nullptr;
		m_depthRenderbuffer = 0;
		m_framebuffer = 0;
	}


} // namespace pl::render
