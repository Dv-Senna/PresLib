#include "image.hpp"



namespace pl::impl::SDL2_renderer::blocks
{
	template <class ...Args>
	Image::Image(
		pl::impl::Instance *instance,
		const std::string &path,
		const pl::math::Vec2f &pos,
		Args ...args
	) : 
		pl::impl::Block(instance),
		m_size {},
		m_state {},
		m_texture {nullptr}
	{
		m_state = pl::states::Image::createStateFromTemplates(path, pos, args...);

		this->m_load();
	}



	void Image::setState(const std::any &state)
	{
		this->m_unload();
		m_state = std::any_cast<pl::states::Image> (state);
		this->m_load();
	}



	std::any Image::getState() const noexcept
	{
		return m_state;
	}



} // namespace pl::impl::SDL2_renderer::blocks
