#include <stdexcept>

#include <SDL2/SDL_gpu.h>

#include "impl/SDL2_gpu/blocks/rectangle.hpp"



namespace pl::impl::SDL2_gpu::blocks
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
		if (m_method == pl::RenderMethod::border)
		{
			GPU_Rectangle(
				std::any_cast<GPU_Target*> (m_instance->getHandler()),
				m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y, m_color
			);
			return;
		}

		GPU_RectangleFilled(
			std::any_cast<GPU_Target*> (m_instance->getHandler()),
			m_pos.x, m_pos.y, m_pos.x + m_size.x, m_pos.y + m_size.y,
			m_color
		);
	}



} // namespace pl::impl::SDL2_gpu::blocks
