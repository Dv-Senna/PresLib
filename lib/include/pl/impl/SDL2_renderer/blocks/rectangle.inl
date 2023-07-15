#include "rectangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Rectangle::Rectangle(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &pos,
		const pl::math::Vec2f &size,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_state {},
		m_size {},
		m_borderThickness {},
		m_texture {nullptr}
	{
		m_state = pl::states::Rectangle::createStateFromTemplates(pos, size, args...);

		this->m_load();
	}



	void Rectangle::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Rectangle> (state);
		this->m_load();
	}



	std::any Rectangle::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
