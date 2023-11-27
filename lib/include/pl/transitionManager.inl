#include "transitionManager.hpp"
#include "transitions/fading.hpp"
#include "transitions/motion.hpp"



namespace pl
{
	template <class T>
	requires (std::is_base_of_v<pl::Transition, T>)
	void TransitionManager::registerTransition(
		const std::list<std::shared_ptr<pl::Slide>>::iterator &slide,
		const pl::Transition::CreateInfo &createInfo,
		const glm::vec2 &viewportSize
	)
	{
		m_transitions[*slide] = std::make_shared<T> (createInfo, viewportSize);
	}



} // namespace pl
