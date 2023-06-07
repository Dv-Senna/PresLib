#include "block/rectangle.hpp"



namespace pl::block
{
	Rectangle::Rectangle(
		pl::Instance &instance,
		const pl::math::Rect &rect,
		const pl::utils::Color &color,
		pl::DrawingType drawingType
	) : 
		pl::Block(instance),
		m_rect {
			static_cast<int> (rect.x),
			static_cast<int> (rect.y),
			static_cast<int> (rect.w),
			static_cast<int> (rect.h)},
		m_color {color},
		m_drawingType {drawingType}
	{
		if (m_color.undefined)
			m_color = m_instance.getColors().getScheme().object;
	}



	void Rectangle::render()
	{
		if (SDL_SetRenderDrawColor(m_instance.getRenderer(), m_color.r, m_color.g, m_color.b, m_color.a) != 0)
			throw std::runtime_error("PL : Can't set rectangle's color : " + std::string(SDL_GetError()));

		if (m_drawingType == pl::DrawingType::filled)
		{
			if (SDL_RenderFillRect(m_instance.getRenderer(), &m_rect) != 0)
				throw std::runtime_error("PL : Can't draw a filled rectangle : " + std::string(SDL_GetError()));
		}

		else if (m_drawingType == pl::DrawingType::outlined)
		{
			if (SDL_RenderDrawRect(m_instance.getRenderer(), &m_rect) != 0)
				throw std::runtime_error("PL : Can't draw an outlined rectangle : " + std::string(SDL_GetError()));
		}

		pl::Block::render();
	}



} // namespace pl::block
