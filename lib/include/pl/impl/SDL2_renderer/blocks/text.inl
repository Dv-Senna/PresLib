#include "text.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Text::Text(
		pl::impl::Instance *instance,
		const std::string &text,
		const pl::math::Vec2f &pos,
		const std::string &font,
		float size,
		Args ...args
	) :
		pl::impl::Block(instance),
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Text::createStateFromTemplates(text, font, pos, size, args...);
		this->m_load();
	}



	void Text::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Text> (state);
		this->m_load();
	}



	std::any Text::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
