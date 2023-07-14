#include "ellipse.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Ellipse::Ellipse(
		pl::impl::Instance *instance,
		const pl::math::Vec2f &center,
		float radius,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Ellipse::createStateFromTemplates(center, radius, args...);
		m_size = {m_state.radius, m_state.radius * sqrt(1 - m_state.excentricity * m_state.excentricity)};

		if (m_state.color == pl::utils::undefined)
			m_state.color = m_instance->getTheme().style.objectColor;

		this->m_load();
	}



	void Ellipse::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Ellipse> (state);
		this->m_load();
	}



	std::any Ellipse::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
