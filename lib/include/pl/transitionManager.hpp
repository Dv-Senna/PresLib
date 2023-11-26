#pragma once

#include <list>
#include <map>
#include <memory>

#include "slide.hpp"
#include "transition.hpp"



namespace pl
{
	struct Instance;

	class TransitionManager final
	{
		public:
			TransitionManager(pl::Instance &instance);
			~TransitionManager() = default;

			void launch(const std::list<std::shared_ptr<pl::Slide>>::iterator &slide);
			template <class T>
			requires (std::is_base_of_v<pl::Transition, T>)
			void registerTransition(
				const std::list<std::shared_ptr<pl::Slide>>::iterator &slide,
				const pl::Transition::CreateInfo &createInfo
			);
			bool isRunning() const noexcept;
			void run(pl::utils::Millisecond dt, glm::mat4 &oldSlide, glm::mat4 &newSlide);
			void stop();


		private:
			pl::Instance &m_instance;
			std::shared_ptr<pl::Slide> m_currentSlide;
			std::map<std::shared_ptr<pl::Slide>, std::shared_ptr<pl::Transition>> m_transitions;
	};

} // namespace pl


#include "transitionManager.inl"