#include <memory>
#include <stdexcept>

#include <SDL2/SDL2_gfxPrimitives.h>

#include "impl/SDL2_renderer/blocks/triangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	Triangle::~Triangle()
	{
		this->m_unload();
	}



	void Triangle::render()
	{
		SDL_FRect rect {m_pos.x, m_pos.y, m_size.x, m_size.y};

		if (SDL_RenderCopyExF(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			m_texture, nullptr, &rect,
			m_state.angle, nullptr, SDL_FLIP_NONE
		) != 0)
			throw std::runtime_error("PL : Can't render triangle : " + std::string(SDL_GetError()));

		this->m_renderChildren();
	}



	void Triangle::m_load()
	{
		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;


		m_size.x = std::max({
			abs(m_state.pos1.x - m_state.pos2.x),
			abs(m_state.pos1.x - m_state.pos3.x),
			abs(m_state.pos2.x - m_state.pos3.x)
		}) * m_state.scale * m_state.distortion.x;
		m_size.y = std::max({
			abs(m_state.pos1.y - m_state.pos2.y),
			abs(m_state.pos1.y - m_state.pos3.y),
			abs(m_state.pos2.y - m_state.pos3.y)
		}) * m_state.scale * m_state.distortion.y;

		float borderThickness {
			m_state.borderThickness * m_state.scale * (m_state.distortion.x + m_state.distortion.y) / 2.f
		};

		pl::math::Vec2f pos1 {m_state.pos1.x * m_state.scale * m_state.distortion.x, m_state.pos1.y * m_state.scale * m_state.distortion.y};
		pl::math::Vec2f pos2 {m_state.pos2.x * m_state.scale * m_state.distortion.x, m_state.pos2.y * m_state.scale * m_state.distortion.y};
		pl::math::Vec2f pos3 {m_state.pos3.x * m_state.scale * m_state.distortion.x, m_state.pos3.y * m_state.scale * m_state.distortion.y};

		pl::math::Vec2f mostTop {};
		pl::math::Vec2f mostLeft {};

		if (pos1.x <= pos2.x && pos1.x <= pos3.x)
			mostLeft = pos1;
		else if (pos2.x <= pos1.x && pos2.x <= pos3.x)
			mostLeft = pos2;
		else
			mostLeft = pos3;

		if (pos1.y <= pos2.y && pos1.y <= pos3.y)
			mostTop = pos1;
		else if (pos2.y <= pos1.y && pos2.y <= pos3.y)
			mostTop = pos2;
		else
			mostTop = pos3;
		
		m_pos.x = mostLeft.x;
		m_pos.y = mostTop.y;

		pos1 -= m_pos;
		pos2 -= m_pos;
		pos3 -= m_pos;


		m_texture = SDL_CreateTexture(
			std::any_cast<SDL_Renderer*> (m_instance->getHandler()),
			SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_TARGET,
			m_size.x, m_size.y
		);

		if (m_texture == nullptr)
			throw std::runtime_error("PL : Can't create texture of tirangle : " + std::string(SDL_GetError()));


		if (SDL_SetRenderTarget(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), m_texture) != 0)
			throw std::runtime_error("PL : Can't change rendering target to triangle's texture : " + std::string(SDL_GetError()));

		SDL_SetTextureBlendMode(m_texture, SDL_BLENDMODE_BLEND);

		if (m_state.renderMethod == pl::RenderMethod::fill)
			s_renderFillTriangle(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), pos1, pos2, pos3);

		else if (m_state.renderMethod == pl::RenderMethod::border)
			s_renderBorderTriangle(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), pos1, pos2, pos3, borderThickness);


		if (SDL_SetRenderTarget(std::any_cast<SDL_Renderer*> (m_instance->getHandler()), nullptr) != 0)
			throw std::runtime_error("PL : Can't change rendering target back to normal from triangle's texture : " + std::string(SDL_GetError()));


		if (SDL_SetTextureColorMod(m_texture, m_state.color.r, m_state.color.g, m_state.color.b) != 0)
			throw std::runtime_error("PL : Can't set triangle's texture color mod : " + std::string(SDL_GetError()));

		if (SDL_SetTextureAlphaMod(m_texture, m_state.color.a) != 0)
			throw std::runtime_error("PL : Can't set triangle's texture alpha mod : " + std::string(SDL_GetError()));
	}



	void Triangle::m_unload()
	{
		if (m_texture != nullptr)
			SDL_DestroyTexture(m_texture);
	}



	void Triangle::s_renderFillTriangle(
		SDL_Renderer *renderer,
		const pl::math::Vec2f &pos1,
		const pl::math::Vec2f &pos2,
		const pl::math::Vec2f &pos3
	)
	{
		if (SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0) != 0)
			throw std::runtime_error("PL : Can't set render draw color to transparent to clean up triangle's texture : " + std::string(SDL_GetError()));

		if (SDL_RenderClear(renderer) != 0)
			throw std::runtime_error("PL : Can't clear triangle's texture : " + std::string(SDL_GetError()));

		filledTrigonColor(renderer,
			pos1.x, pos1.y,
			pos2.x, pos2.y,
			pos3.x, pos3.y,
			0xffffffff
		);
	}



	void Triangle::s_renderBorderTriangle(
		SDL_Renderer *renderer,
		const pl::math::Vec2f &pos1,
		const pl::math::Vec2f &pos2,
		const pl::math::Vec2f &pos3,
		float borderThickness
	)
	{
		if (SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0) != 0)
			throw std::runtime_error("PL : Can't set render draw color to transparent to clean up triangle's texture : " + std::string(SDL_GetError()));

		if (SDL_RenderClear(renderer) != 0)
			throw std::runtime_error("PL : Can't clear triangle's texture : " + std::string(SDL_GetError()));
		
		trigonColor(renderer,
			pos1.x, pos1.y,
			pos2.x, pos2.y,
			pos3.x, pos3.y,
			0xffffffff
		);

		/*thickLineColor(renderer, pos1.x, pos1.y, pos2.x, pos2.y, borderThickness, 0xffffffff);
		thickLineColor(renderer, pos1.x, pos1.y, pos3.x, pos3.y, borderThickness, 0xffffffff);
		thickLineColor(renderer, pos2.x, pos2.y, pos3.x, pos3.y, borderThickness, 0xffffffff);*/
	}



} // namespace pl::impl::SDL2_renderer::blocks
