#include "pl/slide.hpp"

#include "pl/assertation.hpp"
#include "pl/instance.hpp"



namespace pl {
	Slide::Slide(const pl::Slide::CreateInfos &createInfos) :
		m_blocks {},
		m_framebufferMSAA {nullptr},
		m_framebuffer {nullptr},
		m_renderer {},
		m_viewportSize {createInfos.viewportSize},
		m_originalViewportSize {},
		m_instance {nullptr}
	{

	}


	Slide::~Slide() {
		if (m_instance == nullptr)
			return;

		if (m_framebuffer != nullptr)
			m_instance->freeObject(m_framebuffer);
		if (m_framebufferMSAA != nullptr)
			m_instance->freeObject(m_framebufferMSAA);
	}


	void Slide::update() {
		m_renderer.update();
	}


	void Slide::draw() {
		m_renderer.draw(m_framebufferMSAA);
		m_framebuffer->resolveMSAA(*m_framebufferMSAA);
	}


	void Slide::registerBlock(pl::Block *block) {
		m_blocks.push_back(block);
	}


	void Slide::compile(pl::Instance *instance) {
		PL_ASSERT(instance != nullptr, "Can't compile without an instance");

		m_instance = instance;

		if (m_viewportSize.x <= 0)
			m_viewportSize.x = m_instance->getWindow().getSize().x;
		if (m_viewportSize.y <= 0)
			m_viewportSize.y = m_instance->getWindow().getSize().y;

		m_originalViewportSize = m_viewportSize;

		pl::render::Framebuffer::CreateInfos framebufferCreateInfos {};
		framebufferCreateInfos.colorFormat = pl::render::TextureFormat::eRGB8;
		framebufferCreateInfos.size = m_viewportSize;
		framebufferCreateInfos.hasDepth = false;
		framebufferCreateInfos.multisampled = true;
		m_framebufferMSAA = m_instance->allocateObject<pl::render::Framebuffer> (framebufferCreateInfos);

		framebufferCreateInfos.multisampled = false;
		m_framebuffer = m_instance->allocateObject<pl::render::Framebuffer> (framebufferCreateInfos);

		for (auto &block : m_blocks) {
			block->compile(instance);
			block->updateTransform();
		}

		m_renderer.compile(m_instance, m_blocks);
	}


	void Slide::resize(const pl::Vec2i &size) {
		m_framebufferMSAA->resize(size);
		m_framebuffer->resize(size);
		m_viewportSize = size;
	}


} // namespace pl
