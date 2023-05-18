#include <cassert>
#include <stdexcept>

#include "block/line.hpp"



namespace pl::block
{
	Line::Line(
		pl::Instance &instance,
		pl::math::Vec2 start,
		pl::math::Vec2 end,
		const pl::utils::Color color
	) :
		pl::Block(instance),
		m_start {start},
		m_end {end},
		m_color {color}
	{

	}



	void Line::render()
	{
		if (SDL_SetRenderDrawColor(m_instance.getRenderer(), m_color.r, m_color.g, m_color.b, m_color.a) != 0)
			throw std::runtime_error("PL : Can't set line's color : " + std::string(SDL_GetError()));

		if (SDL_RenderDrawLine(m_instance.getRenderer(), m_start.x, m_start.y, m_end.x, m_end.y) != 0)
			throw std::runtime_error("PL : Can't draw a line : " + std::string(SDL_GetError()));
	}



	void Line::addChildren(pl::Block *block)
	{
		assert(block && "PL : don't call addChildren on a line block");
	}



	void Line::removeChildren(pl::Block *block)
	{
		assert(block && "PL : don't call removeChildren on a line block");
	}





} // namespace pl::block
