#include "pl/instance.hpp"

#include <iostream>
#include <stdexcept>

#include <SDL2/SDL.h>

#include "pl/assertation.hpp"



namespace pl {
	Instance::Instance(const pl::Instance::CreateInfos &createInfos) :
		m_blockFactory {{
			.heapSize = createInfos.blockHeapSize
		}},
		m_window {nullptr},
		m_slides {},
		m_slidesOrder {},
		m_currentSlide {0}
	{
		std::cout << "Create Instance of PresLib" << std::endl;
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("Can't init SDL2 : " + std::string(SDL_GetError()));

		pl::Window::CreateInfos windowCreateInfos {};
		windowCreateInfos.title = createInfos.presentationName;
		windowCreateInfos.size = createInfos.viewportSize;
		m_window = new pl::Window(windowCreateInfos);
	}


	Instance::~Instance() {
		std::cout << "Destroy Instance of PresLib" << std::endl;
		if (m_window != nullptr)
			delete m_window;
		SDL_Quit();
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
		return false;
	}


	void Instance::previousSlide() {
		if (m_currentSlide > 0)
			--m_currentSlide;
	}


} // namespace pl
