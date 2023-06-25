#include "impl/SDL2_renderer/blocks/line.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Line::Line(pl::impl::Instance *instance, int startx, int starty, int endx, int endy) : 
		pl::impl::Block(instance),
		m_startx {startx}, m_starty {starty}, m_endx {endx}, m_endy {endy}
	{

	}



	Line::~Line()
	{

	}



	void Line::render()
	{
		SDL_RenderDrawLine(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), m_startx, m_starty, m_endx, m_endy);
	}



} // namespace pl::impl::SDL2_renderer::blocks
