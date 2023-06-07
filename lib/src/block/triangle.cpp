#include <SDL2/SDL.h>

#include "block/triangle.hpp"



namespace pl::block
{
	Triangle::Triangle(
		pl::Instance &instance,
		const std::array<pl::math::Vec2, 3> &vertices,
		const pl::utils::Color &color,
		pl::DrawingType drawingType
	) :
		pl::Block(instance),
		m_vertices {std::move(vertices)},
		m_verticesSDL {
			SDL_Vertex(SDL_FPoint(m_vertices[0].x, m_vertices[0].y), {color.r, color.g, color.b, color.a}, {}),
			SDL_Vertex(SDL_FPoint(m_vertices[1].x, m_vertices[1].y), {color.r, color.g, color.b, color.a}, {}),
			SDL_Vertex(SDL_FPoint(m_vertices[2].x, m_vertices[2].y), {color.r, color.g, color.b, color.a}, {})
		},
		m_color {color},
		m_drawingType {drawingType}
	{
		if (m_color.undefined)
		{
			m_color = m_instance.getColors().getScheme().object;

			for (auto &vertex : m_verticesSDL)
				vertex.color = m_color;
		}
	}



	void Triangle::render()
	{
		if (m_drawingType == pl::DrawingType::outlined)
		{
			if (SDL_SetRenderDrawColor(
				m_instance.getRenderer(),
				m_color.r, m_color.g, m_color.b, m_color.a) != 0)
				throw std::runtime_error("PL : Can't set triangle's color : " + std::string(SDL_GetError()));

			if (SDL_RenderDrawLine(
				m_instance.getRenderer(),
				m_vertices[0].x, m_vertices[0].y,
				m_vertices[1].x, m_vertices[1].y) != 0)
				throw std::runtime_error("PL : Can't draw a line for triangle : " + std::string(SDL_GetError()));

			if (SDL_RenderDrawLine(
				m_instance.getRenderer(),
				m_vertices[1].x, m_vertices[1].y,
				m_vertices[2].x, m_vertices[2].y) != 0)
				throw std::runtime_error("PL : Can't draw a line for triangle : " + std::string(SDL_GetError()));

			if (SDL_RenderDrawLine(
				m_instance.getRenderer(),
				m_vertices[2].x, m_vertices[2].y,
				m_vertices[0].x, m_vertices[0].y) != 0)
				throw std::runtime_error("PL : Can't draw a line for triangle : " + std::string(SDL_GetError()));
		}

		else if (m_drawingType == pl::DrawingType::filled)
		{
			if (SDL_RenderGeometry(
				m_instance.getRenderer(),
				nullptr,
				m_verticesSDL.data(), 3,
				nullptr, 0) != 0)
				throw std::runtime_error("PL : Can't draw filled triangle : " + std::string(SDL_GetError()));
		}
	}



} // namespace pl::block