#include "instance.hpp"



namespace pl
{
	template <class T>
	requires (std::is_base_of_v<pl::Transition, T>)
	void Instance::registerTransition(
		std::shared_ptr<pl::Slide> slide,
		const pl::Transition::CreateInfo &createInfo
	)
	{
		auto it {std::find(m_slides.begin(), m_slides.end(), slide)};
		if (it == m_slides.end())
			throw std::invalid_argument("PL : Can't add transition to the given slide because the slide wasn't registered");

		m_transitionManager.registerTransition<T> (it, createInfo);
	}



} // namespace pl
