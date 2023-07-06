#include <stdexcept>

#include "impl/SDL2_renderer/blocks/line.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Line::Line(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &start,
		const pl::math::Vec2f &end,
		const pl::utils::Color &color
	) : 
		pl::impl::Block(instance),
		m_start {start},
		m_end {end},
		m_color {color}
	{

	}



	Line::~Line()
	{

	}



	void Line::render()
	{
		if (SDL_SetRenderDrawColor(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
			throw std::runtime_error("PL : Can't change line draw color : " + std::string(SDL_GetError()));

		if (SDL_RenderDrawLineF(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), 
				m_start.x, m_start.y, m_end.x, m_end.y
			))
			throw std::runtime_error("PL : Can't draw line : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



} // namespace pl::impl::SDL2_renderer::blocks
