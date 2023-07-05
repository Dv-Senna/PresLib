#include <stdexcept>

#include "impl/SDL2_renderer/blocks/triangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Triangle::Triangle(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &a,
		const pl::math::Vec2f &b,
		const pl::math::Vec2f &c,
		const pl::utils::Color &color,
		pl::RenderMethod method
	) : 
		pl::impl::Block(instance),
		m_a {a},
		m_b {b},
		m_c {c},
		m_color {color},
		m_method {method}
	{

	}



	Triangle::~Triangle()
	{

	}



	void Triangle::render()
	{
		if (m_method == pl::RenderMethod::border)
		{
			if (SDL_SetRenderDrawColor(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
			throw std::runtime_error("PL : Can't change triangle draw color : " + std::string(SDL_GetError()));

			SDL_FPoint points[4] {{m_a.x, m_a.y}, {m_b.x, m_b.y}, {m_c.x, m_c.y}, {m_a.x, m_a.y}};

			if (SDL_RenderDrawLinesF(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), points, 4) != 0)
				throw std::runtime_error("PL : Can't render border triangle : " + std::string(SDL_GetError()));
		
			return;
		}
		
		SDL_Vertex vertices[3] {
			{{m_a.x, m_a.y}, {m_color.r, m_color.g, m_color.b, m_color.a}, {}},
			{{m_b.x, m_b.y}, {m_color.r, m_color.g, m_color.b, m_color.a}, {}},
			{{m_c.x, m_c.y}, {m_color.r, m_color.g, m_color.b, m_color.a}, {}}
		};

		if (SDL_RenderGeometry(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			nullptr, vertices, 3, nullptr, 0
		) != 0)
			throw std::runtime_error("PL : Can't render fill triangle : " + std::string(SDL_GetError()));


		this->m_renderChildren();
	}



} // namespace pl::impl::SDL2_renderer::blocks
