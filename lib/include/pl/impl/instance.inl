#pragma once

#include <stdexcept>

#include "instance.hpp"



namespace pl::impl
{
	Instance::Instance() :
		m_window {nullptr},
		m_windowInfos {},
		m_renderingCallback {nullptr},
		m_children {}
	{
		m_windowInfos.width = 16 * 70;//1920;
		m_windowInfos.height = 9 * 70;//1080;
		m_windowInfos.title = "PresLib";
		m_windowInfos.flags = SDL_WINDOW_SHOWN;

		if (SDL_Init(SDL_INIT_VIDEO) != 0)
			throw std::runtime_error("PL : Can't init SDL2 : " + std::string(SDL_GetError()));
	}



	Instance::~Instance()
	{
		SDL_DestroyWindow(m_window);
		SDL_Quit();
	}



	void Instance::setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept
	{
		m_renderingCallback = std::move(callback);
	}



	SDL_Window *Instance::getWindow() const noexcept
	{
		return m_window;
	}



	const pl::utils::WindowInfos &Instance::getWindowInfos() const noexcept
	{
		return m_windowInfos;
	}



	void Instance::m_createWindow()
	{
		m_window = SDL_CreateWindow(
			m_windowInfos.title.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			m_windowInfos.width, m_windowInfos.height,
			m_windowInfos.flags
		);
		if (m_window == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 window : " + std::string(SDL_GetError()));
	}



	void Instance::addChildren(pl::impl::Block *child)
	{
		m_children.push_back(child);
	}



} // namespace pl::impl
