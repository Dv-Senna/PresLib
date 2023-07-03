#include <stdexcept>

#include <SDL2/SDL_gpu.h>

#include "impl/SDL2_gpu/blocks/triangle.hpp"



namespace pl::impl::SDL2_gpu::blocks
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
			return;
		}
		
		float vertices[6] {
			m_a.x, m_a.y,
			m_b.x, m_b.y,
			m_c.x, m_c.y
		};

		GPU_TriangleBatch(nullptr, std::any_cast<GPU_Target*> (m_instance->getHandler()), 3, vertices, 0, nullptr, GPU_USE_DEFAULT_POSITIONS);
	}



} // namespace pl::impl::SDL2_gpu::blocks
