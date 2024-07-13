#include "pl/render/framebuffer.hpp"

#include <map>
#include <stdexcept>

#include <glad/gl.h>



namespace pl::render {
	Framebuffer::Framebuffer(const pl::render::Framebuffer::CreateInfos &infos) :
		m_colorFormat {},
		m_size {infos.size},
		m_colorTexture {0},
		m_depthRenderbuffer {0},
		m_framebuffer {0}
	{
		static const std::map<pl::render::FramebufferColorFormat, GLenum> colorFormatMap {
			{pl::render::FramebufferColorFormat::eRGB8,         GL_RGB8},
			{pl::render::FramebufferColorFormat::eRGBA8,        GL_RGBA8},
			{pl::render::FramebufferColorFormat::eRGB32f,       GL_RGB32F},
			{pl::render::FramebufferColorFormat::eRGBA32f,      GL_RGBA32F},
			{pl::render::FramebufferColorFormat::eR11fG11fB10f, GL_R11F_G11F_B10F},
		};

		m_colorFormat = colorFormatMap.find(infos.colorFormat)->second;
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

	}


	void Framebuffer::m_create(bool depthBuffer) {
		glCreateTextures(GL_TEXTURE_2D, 1, &m_colorTexture);
		glTextureStorage2D(m_colorTexture, 1, m_colorFormat, m_size.x, m_size.y);

		glCreateFramebuffers(1, &m_framebuffer);
		glNamedFramebufferTexture(m_framebuffer, GL_COLOR_ATTACHMENT0, m_colorTexture, 0);

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
		if (m_colorTexture != 0)
			glDeleteTextures(1, &m_colorTexture);
		
		m_colorFormat = 0;
		m_depthRenderbuffer = 0;
		m_framebuffer = 0;
	}


} // namespace pl::render
