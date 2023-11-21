#pragma once

#include <map>
#include <memory>
#include <list>

#include "animation.hpp"
#include "eventManager.hpp"
#include "slide.hpp"



namespace pl
{
	class AnimationManager final
	{
		public:
			AnimationManager();
			~AnimationManager() = default;

			bool handleEvent(std::shared_ptr<pl::Slide> slide, const pl::EventManager &eventManager);
			void run(std::shared_ptr<pl::Slide> slide, float dt);
			void wentToNextSlide(std::shared_ptr<pl::Slide> slide);

			std::shared_ptr<pl::Animation> addAnimation(std::shared_ptr<pl::Slide> slide, const pl::Animation::CreateInfo &createInfos);
			std::shared_ptr<pl::Animation> addAnimation(std::shared_ptr<pl::Slide> slide, std::shared_ptr<pl::Animation> animation);


		private:
			static std::shared_ptr<pl::Animation> s_createAnimation(const pl::Animation::CreateInfo &createInfo);

			std::map<std::shared_ptr<pl::Slide>, std::list<std::shared_ptr<pl::Animation>>> m_animations;
			std::map<std::shared_ptr<pl::Slide>, std::list<std::shared_ptr<pl::Animation>>::iterator> m_nextAnimation;
	};

} // namespace pl
