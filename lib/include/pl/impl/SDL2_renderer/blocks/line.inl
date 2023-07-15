#include "line.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Line::Line(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &start,
		const pl::math::Vec2f &end,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_pos {},
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Line::createStateFromTemplates(start, end, args...);

		this->m_load();
	}



	void Line::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Line> (state);
		this->m_load();
	}



	std::any Line::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
