#include "math.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Math::Math(
		pl::impl::Instance *instance,
		const std::string &equation,
		const pl::math::Vec2f &pos,
		float size,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Math::createStateFromTemplates(equation, pos, size, args...);

		this->m_load();
	}



	void Math::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Math> (state);
		this->m_load();
	}



	std::any Math::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
