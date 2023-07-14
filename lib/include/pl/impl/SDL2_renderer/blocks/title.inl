#include "title.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	void Title::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Title> (state);
		this->m_load();
	}



	std::any Title::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
