#include "theme.hpp"



namespace pl
{
	Theme::Theme(pl::Instance &instance) : m_instance {instance}, m_style {}
	{

	}



	const pl::Style &Theme::getStyle() const noexcept
	{
		return m_style;
	}

} // namespace pl
