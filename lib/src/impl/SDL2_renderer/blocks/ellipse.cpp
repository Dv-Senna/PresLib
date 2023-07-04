#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL2_rotozoom.h>

#include "impl/SDL2_renderer/blocks/ellipse.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Ellipse::Ellipse(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &center,
		float radius,
		float excentricity,
		float angle,
		const pl::utils::Color &color,
		pl::RenderMethod method
	) : 
		pl::impl::Block(instance),
		m_center {center},
		m_size {radius, radius * sqrt(1 - excentricity)},
		m_angle {angle},
		m_color {color},
		m_method {method}
	{

	}



	Ellipse::~Ellipse()
	{

	}



	void Ellipse::render()
	{
		/*if (SDL_SetRenderDrawColor(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
			throw std::runtime_error("PL : Can't change ellipse draw color : " + std::string(SDL_GetError()));*/


		if (m_size.x == m_size.y)
		{
			if (m_method == pl::RenderMethod::border)
			{
				if (aacircleRGBA(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
					m_center.x, m_center.y, m_size.x, m_color.r, m_color.g, m_color.b, m_color.a
				) != 0)
					throw std::runtime_error("PL : Can't render outlined circle : " + std::string(SDL_GetError()));

				return;
			}

			if (filledCircleRGBA(std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_center.x, m_center.y, m_size.x, m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
				throw std::runtime_error("PL : Can't render filled circle : " + std::string(SDL_GetError()));

			return;
		}



		if (m_method == pl::RenderMethod::border)
		{
			if (aaellipseRGBA(
				std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_center.x, m_center.y, m_size.x, m_size.y, m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
				throw std::runtime_error("PL : Can't render outlined ellipse : " + std::string(SDL_GetError()));

			return;
		}
		
		if (filledEllipseRGBA(
				std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
				m_center.x, m_center.y, m_size.x, m_size.y, m_color.r, m_color.g, m_color.b, m_color.a
			) != 0)
				throw std::runtime_error("PL : Can't render filled ellipse : " + std::string(SDL_GetError()));
	}



} // namespace pl::impl::SDL2_renderer::blocks
