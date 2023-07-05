#include <stdexcept>

#include "impl/SDL2_renderer/blocks/rectangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Rectangle::Rectangle(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &pos,
		const pl::math::Vec2f &size,
		const pl::utils::Color &color,
		pl::RenderMethod method
	) : 
		pl::impl::Block(instance),
		m_pos {pos},
		m_size {size},
		m_color {color},
		m_method {method}
	{

	}



	Rectangle::~Rectangle()
	{

	}



	void Rectangle::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_SetRenderDrawColor(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
			throw std::runtime_error("PL : Can't change rectangle draw color : " + std::string(SDL_GetError()));

		if (m_method == pl::RenderMethod::border)
		{
			if (SDL_RenderDrawRectF(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), &rect) != 0)
				throw std::runtime_error("PL : Can't render border rect : " + std::string(SDL_GetError()));

			return;
		}
		
		if (SDL_RenderFillRectF(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), &rect) != 0)
			throw std::runtime_error("PL : Can't render fill rect : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



} // namespace pl::impl::SDL2_renderer::blocks
