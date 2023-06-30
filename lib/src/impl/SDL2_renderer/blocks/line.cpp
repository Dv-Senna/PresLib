#include "impl/SDL2_renderer/blocks/line.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Line::Line(pl::impl::Instance *instance, const pl::math::Vec2f &start, const pl::math::Vec2f &end) : 
		pl::impl::Block(instance),
		m_start {start},
		m_end {end}
	{

	}



	Line::~Line()
	{

	}



	void Line::render()
	{
		SDL_RenderDrawLine(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), 
			static_cast<int> (m_start.x),
			static_cast<int> (m_start.y),
			static_cast<int> (m_end.x),
			static_cast<int> (m_end.y)
		);
	}



} // namespace pl::impl::SDL2_renderer::blocks
