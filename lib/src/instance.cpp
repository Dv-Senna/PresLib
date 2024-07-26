#include "pl/instance.hpp"

#include <iostream>
#include <stdexcept>

#include <glad/gl.h>
#include <SDL2/SDL.h>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "pl/assertation.hpp"
#include "pl/config.hpp"
#include "pl/inputManager.hpp"
#include "pl/resourceManager.hpp"



namespace pl {
	Instance::Instance(const pl::Instance::CreateInfos &createInfos) :
		m_window {nullptr},
		m_slides {},
		m_slidesOrder {},
		m_currentSlide {0},
		m_objectHeapAllocator {{
			.size = createInfos.objectHeapSize
		}},
		m_objectHeapManager {{
			.allocator = &m_objectHeapAllocator
		}},
		m_viewportRect {0, 0, createInfos.viewportSize.x, createInfos.viewportSize.y}
	{
		std::cout << "Create Instance of PresLib" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Can't init SDL2 : " + std::string(SDL_GetError()));

		pl::Window::CreateInfos windowCreateInfos {};
		windowCreateInfos.title = createInfos.presentationName;
		windowCreateInfos.size = createInfos.viewportSize;
		m_window = m_objectHeapManager.allocate<pl::Window> (windowCreateInfos);

		pl::ResourceManager::CreateInfos resourceManagerCreateInfos {};
		resourceManagerCreateInfos.instance = this;
		resourceManagerCreateInfos.heapSize = createInfos.resourceHeapSize;
		pl::ResourceManager::create(resourceManagerCreateInfos);
	}


	Instance::~Instance() {
		std::cout << "Destroy Instance of PresLib" << std::endl;
		pl::ResourceManager::destroy();

		if (m_window != nullptr)
			m_objectHeapManager.free(m_window);
		SDL_Quit();
	}


	void Instance::mainloop() {
		for (auto &slide : m_slides)
			slide.second->compile(this);

		this->m_calculateViewportRect();

		pl::Float deltaTime {0};
		pl::Uint32 startFrameTime {SDL_GetTicks()};

		while (pl::InputManager::isRunning()) {
			pl::InputManager::update();
			if (pl::InputManager::isKeyDown(pl::Key::eEscape))
				return;

			if (pl::InputManager::wasKeyPressed(pl::Key::eSpace) || pl::InputManager::wasKeyPressed(pl::Key::eRight)) {
				if (this->nextSlide())
					return;
			}

			if (pl::InputManager::wasKeyPressed(pl::Key::eLeft))
				this->previousSlide();

			if (pl::InputManager::wasWindowResized())
				this->handleResize();

			glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
			glClearColor(0.f, 0.f, 0.f, 1.f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_slidesOrder[m_currentSlide]->second->update();
			m_slidesOrder[m_currentSlide]->second->draw();

			glBlitNamedFramebuffer(
				m_slidesOrder[m_currentSlide]->second->getFramebuffer().getFramebuffer(),
				0,
				0, 0, m_slidesOrder[m_currentSlide]->second->getViewportSize().x, m_slidesOrder[m_currentSlide]->second->getViewportSize().y,
				m_viewportRect.x, m_viewportRect.y, m_viewportRect.x + m_viewportRect.w, m_viewportRect.y + m_viewportRect.h,
				GL_COLOR_BUFFER_BIT, GL_NEAREST
			);

			if (pl::Config::getCustomRenderCallback() != nullptr)
				pl::Config::getCustomRenderCallback()();

			m_window->swap();

			pl::Uint32 endFrameTime {SDL_GetTicks()};
			pl::Float elapsedTime {static_cast<pl::Float> (endFrameTime - startFrameTime)};
			if (elapsedTime < deltaTime) {
				SDL_Delay(static_cast<pl::Uint32> (deltaTime - elapsedTime));
				deltaTime = pl::Config::getFrameDuration();
			}
			else
				deltaTime = elapsedTime;
			startFrameTime = SDL_GetTicks();
		}
	}


	void Instance::registerSlide(const std::string &name, pl::Slide *slide) {
		m_slides[name] = slide;
		auto it {m_slides.find(name)};
		m_slidesOrder.push_back(it);
	}


	pl::Slide *Instance::getSlide(const std::string &name) {
		auto it {m_slides.find(name)};
		PL_ASSERT(it != m_slides.end(), "Invalid slide name");
		return it->second;
	}


	pl::Slide *Instance::getSlide(pl::Count index) {
		PL_ASSERT(index < m_slidesOrder.size(), "Invalid slide index");
		auto it {m_slidesOrder[index]};
		return it->second;
	}


	bool Instance::nextSlide() {
		++m_currentSlide;
		if (m_currentSlide >= m_slidesOrder.size())
			return true;
		this->m_calculateViewportRect();
		return false;
	}


	void Instance::previousSlide() {
		if (m_currentSlide <= 0)
			return;
		--m_currentSlide;
		this->m_calculateViewportRect();
	}


	void Instance::handleResize() {
		m_window->handleResize();
		this->m_calculateViewportRect();
	}


	void Instance::m_calculateViewportRect() {
		const pl::Vec2i &viewportSize {m_slidesOrder[m_currentSlide]->second->getOriginalViewportSize()};

		pl::Float32 ratioScreen {m_window->getSize().x / static_cast<pl::Float32> (m_window->getSize().y)};
		pl::Float32 ratioViewport {viewportSize.x / static_cast<pl::Float32> (viewportSize.y)};

		if (ratioScreen == ratioViewport)
			m_viewportRect = {0, 0, m_window->getSize().x, m_window->getSize().y};

		else if (ratioScreen < ratioViewport) {
			pl::Float32 ratio {ratioScreen / ratioViewport};
			m_viewportRect.x = 0;
			m_viewportRect.w = m_window->getSize().x;
			m_viewportRect.h = ratio * m_window->getSize().y;
			m_viewportRect.y = (m_window->getSize().y - m_viewportRect.h) * 0.5f;
		}

		else {
			pl::Float32 ratio {ratioViewport / ratioScreen};
			m_viewportRect.y = 0;
			m_viewportRect.h = m_window->getSize().y;
			m_viewportRect.w = ratio * m_window->getSize().x;
			m_viewportRect.x = (m_window->getSize().x - m_viewportRect.w) * 0.5f;
		}

		m_slidesOrder[m_currentSlide]->second->resize({m_viewportRect.w, m_viewportRect.h});
	}


} // namespace pl
