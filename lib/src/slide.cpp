#include "pl/slide.hpp"

#include "pl/assertation.hpp"
#include "pl/instance.hpp"



namespace pl {
	Slide::Slide() :
		m_blocks {},
		m_framebuffer {nullptr},
		m_renderer {},
		m_instance {nullptr}
	{

	}


	Slide::~Slide() {
		if (m_instance == nullptr)
			return;

		if (m_framebuffer != nullptr)
			m_instance->freeObject(m_framebuffer);
	}


	void Slide::update() {

	}


	void Slide::draw() {
		m_renderer.draw(/*m_framebuffer*/nullptr);
	}


	void Slide::registerBlock(pl::Block *block) {
		m_blocks.push_back(block);
	}


	void Slide::compile(pl::Instance *instance) {
		PL_ASSERT(instance != nullptr, "Can't compile without an instance");

		m_instance = instance;

		pl::render::Framebuffer::CreateInfos framebufferCreateInfos {};
		framebufferCreateInfos.colorFormat = pl::render::FramebufferColorFormat::eRGB8;
		framebufferCreateInfos.size = m_instance->getWindow().getSize();
		framebufferCreateInfos.hasDepth = false;
		m_framebuffer = m_instance->allocateObject<pl::render::Framebuffer> (framebufferCreateInfos);

		for (auto &block : m_blocks)
			block->compile(instance);

		m_renderer.compile(m_instance, m_blocks);
	}


} // namespace pl
