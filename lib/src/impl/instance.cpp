#include <iostream>

#include "impl/block.hpp"
#include "slide.hpp"
#include "impl/instance.hpp"



namespace pl::impl
{
	bool Instance::m_handleEvent()
	{
		static SDL_Event event {};

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_KEYDOWN)
			{
				#ifndef NDEBUG

					if (event.key.keysym.scancode == SDL_SCANCODE_D)
					{
						std::cout << "---------------- Debug log start ----------------" << std::endl;

						std::cout << "Current slide : " << *m_currentSlide << std::endl;

						for (auto slide : m_slides)
							std::cout << "Slide : " << slide << " : contains " << slide->getBlocks().size() << " blocks" << std::endl;

						std::cout << "----------------  Debug log end  ----------------" << std::endl;
					}

				#endif

				else if (event.key.keysym.scancode == SDL_SCANCODE_RIGHT)
				{
					m_currentSlide++;

					if (m_currentSlide == m_slides.end())
						return false;
				}

				else if (event.key.keysym.scancode == SDL_SCANCODE_LEFT)
				{
					if (m_currentSlide != m_slides.begin())
						m_currentSlide--;
				}

				else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return false;
			}

			else if (event.type == SDL_QUIT)
				return false;
		}

		return true;
	}



	void Instance::m_render()
	{
		if (m_currentSlide != m_slides.end())
		{
			if (!((*m_currentSlide)->getFlags() & pl::SlideFlag::noBackground) && m_background != nullptr)
				m_background->render();

			else if (!((*m_currentSlide)->getFlags() & pl::SlideFlag::noBackground) && m_theme->style.background != nullptr)
				m_theme->style.background->render();

			(*m_currentSlide)->render();

			if (!((*m_currentSlide)->getFlags() & pl::SlideFlag::noForeground) && m_foreground != nullptr)
				m_foreground->render();

			else if (!((*m_currentSlide)->getFlags() & pl::SlideFlag::noForeground) && m_theme->style.foreground != nullptr)
				m_theme->style.foreground->render();
		}

		
		if (m_renderingCallback != nullptr)
			m_renderingCallback(this);
	}



} // namespace pl::impl
