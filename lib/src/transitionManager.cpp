#include "transitionManager.hpp"



namespace pl
{
	TransitionManager::TransitionManager(pl::Instance &instance) : 
		m_instance {instance},
		m_currentSlide {},
		m_transitions {}
	{

	}



	void TransitionManager::launch(const std::list<std::shared_ptr<pl::Slide>>::iterator &slide)
	{
		m_currentSlide = *slide;
		auto it {m_transitions.find(m_currentSlide)};
		if (it == m_transitions.end())
			return;

		it->second->launch();
	}



	bool TransitionManager::isRunning() const noexcept
	{
		auto it {m_transitions.find(m_currentSlide)};
		if (it == m_transitions.end())
			return false;

		return it->second->isRunning();
	}



	void TransitionManager::run(pl::utils::Millisecond dt, glm::mat4 &oldSlide, glm::mat4 &newSlide)
	{
		auto it {m_transitions.find(m_currentSlide)};
		if (it == m_transitions.end())
			return;

		it->second->run(dt, oldSlide, newSlide);
	}



	void TransitionManager::stop()
	{
		auto it {m_transitions.find(m_currentSlide)};
		if (it == m_transitions.end())
			return;

		it->second->stop();
	}



} // namespace pl
