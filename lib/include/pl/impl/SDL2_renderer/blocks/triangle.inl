#include "triangle.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Triangle::Triangle(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &pos1,
		const pl::math::Vec2f &pos2,
		const pl::math::Vec2f &pos3,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_pos {},
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Triangle::createStateFromTemplates(pos1, pos2, pos3, args...);

		this->m_load();
	}



	void Triangle::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Triangle> (state);
		this->m_load();
	}



	std::any Triangle::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
