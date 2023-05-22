#include "theme.hpp"



namespace pl
{
	Theme::Theme(pl::Instance &instance) : 
		m_instance {instance},
		m_background {nullptr},
		m_overlay {nullptr},
		m_scheme {pl::defaultColorScheme},
		m_titlePosition {},
		m_titleFontSize {}
	{

	}



	Theme::~Theme()
	{

	}



	void Theme::use()
	{
		if (m_background != nullptr)
			m_instance.setSharedBackground(m_background.get());

		if (m_overlay != nullptr)
			m_instance.setSharedBackground(m_overlay.get());

		m_instance.getColors().setScheme(m_scheme);
		m_instance.setTitlePosition(m_titlePosition);
		m_instance.setTitleFontSize(m_titleFontSize);
	}



} // namespace pl