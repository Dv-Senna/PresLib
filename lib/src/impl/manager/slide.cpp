#include "manager/event.hpp"
#include "slide.hpp"
#include "impl/manager/slide.hpp"



namespace pl::impl::manager
{
	Slide::Slide() : 
		m_slides {},
		m_currentSlide {m_slides.begin()}
	{

	}



	void Slide::add(pl::impl::Slide *slide)
	{
		m_slides.push_back(slide);
		if (m_slides.size() == 1)
			m_currentSlide = m_slides.begin();
	}



	void Slide::draw()
	{
		if (m_currentSlide != m_slides.end())
			(*m_currentSlide)->draw();
	}



	bool Slide::process(pl::impl::manager::Event *eventManager)
	{
		if (
			eventManager->getKeys()[pl::utils::keys::space].isDown && eventManager->getKeys()[pl::utils::keys::space].hasChanged
			|| eventManager->getKeys()[pl::utils::keys::right].isDown && eventManager->getKeys()[pl::utils::keys::right].hasChanged
		)
		{
			++m_currentSlide;
			if (m_currentSlide == m_slides.end())
				return false;
		}

		if (eventManager->getKeys()[pl::utils::keys::left].isDown && eventManager->getKeys()[pl::utils::keys::left].hasChanged)
		{
			if (m_currentSlide != m_slides.begin())
				--m_currentSlide;
		}

		return true;
	}



} // namespace pl::impl::manager
