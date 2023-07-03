#pragma once

#include <stdexcept>

#include "instance.hpp"



namespace pl::impl
{
	Instance::Instance() :
		m_window {nullptr},
		m_windowInfos {},
		m_renderingCallback {nullptr},
		m_slides {},
		m_currentSlide {m_slides.begin()}
	{
		m_windowInfos.width = 16 * 70;//1920;
		m_windowInfos.height = 9 * 70;//1080;
		m_windowInfos.title = "PresLib";
		m_windowInfos.flags = SDL_WINDOW_SHOWN;
	}



	void Instance::setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept
	{
		m_renderingCallback = std::move(callback);
	}



	std::any Instance::getWindow() const noexcept
	{
		return m_window;
	}



	const pl::utils::WindowInfos &Instance::getWindowInfos() const noexcept
	{
		return m_windowInfos;
	}



	void Instance::addSlide(pl::Slide *slide)
	{
		m_slides.push_back(slide);

		if (m_slides.size() == 1)
			m_currentSlide = m_slides.begin();
	}



	void Instance::m_initSDL2()
	{
		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("PL : Can't init SDL2 : " + std::string(SDL_GetError()));

		m_window = SDL_CreateWindow(
			m_windowInfos.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_windowInfos.width, m_windowInfos.height,
			m_windowInfos.flags
		);
		if (std::any_cast<SDL_Window*> (m_window) == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 window : " + std::string(SDL_GetError()));
	}



	void Instance::m_quitSDL2()
	{
		SDL_DestroyWindow(std::any_cast<SDL_Window*> (m_window));
		SDL_Quit();
	}



} // namespace pl::impl
