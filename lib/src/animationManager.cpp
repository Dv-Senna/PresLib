#include <iostream>

#include "animationManager.hpp"
#include "animations/motion.hpp"
#include "animations/rotation.hpp"



namespace pl
{
	AnimationManager::AnimationManager() : 
		m_animations {},
		m_nextAnimation {}
	{

	}



	bool AnimationManager::handleEvent(std::shared_ptr<pl::Slide> slide, const pl::EventManager &eventManager)
	{
		if (eventManager.isKeyPressed(SDL_SCANCODE_LEFT))
		{
			bool isOneAnimationPlaying {false};
			for (auto &animation : m_animations[slide])
			{
				if (animation->isRunning())
				{
					isOneAnimationPlaying = true;
					animation->goToStart();
				}
			}
			

			if (!isOneAnimationPlaying && (m_animations[slide].empty() || m_nextAnimation[slide] == m_animations[slide].begin()))
				return true;

			--m_nextAnimation[slide];
			m_nextAnimation[slide]->get()->goToStart();
		}


		if (eventManager.isKeyPressed(SDL_SCANCODE_RIGHT) || eventManager.isKeyPressed(SDL_SCANCODE_SPACE))
		{
			bool isOneAnimationPlaying {false};
			for (auto &animation : m_animations[slide])
			{
				if (animation->isRunning())
				{
					isOneAnimationPlaying = true;
					animation->skipToEnd();
				}
			}


			if (!isOneAnimationPlaying)
			{
				if (m_animations[slide].empty() || m_nextAnimation[slide] == m_animations[slide].end())
					return true;

				m_nextAnimation[slide]->get()->launch();
				++m_nextAnimation[slide];

				for (; m_nextAnimation[slide] != m_animations[slide].end(); ++m_nextAnimation[slide])
				{
					if (m_nextAnimation[slide]->get()->getStartFlag() != pl::Animation::StartFlag::withPrevious)
						break;
					
					m_nextAnimation[slide]->get()->launch();
				}
			}
		}

		return false;
	}



	void AnimationManager::run(std::shared_ptr<pl::Slide> slide, float dt)
	{
		for (auto &animation : m_animations[slide])
		{
			if (animation->isRunning())
				animation->run(dt);
		}
	}



	void AnimationManager::wentToNextSlide(std::shared_ptr<pl::Slide> slide)
	{
		if (m_animations[slide].empty())
			return;

		if (m_nextAnimation[slide]->get()->getStartFlag() == pl::Animation::StartFlag::withPrevious)
		{
			m_nextAnimation[slide]->get()->launch();
			++m_nextAnimation[slide];

			for (; m_nextAnimation[slide] != m_animations[slide].end(); ++m_nextAnimation[slide])
			{
				if (m_nextAnimation[slide]->get()->getStartFlag() != pl::Animation::StartFlag::withPrevious)
					break;
				
				m_nextAnimation[slide]->get()->launch();
			}
		}
	}



	std::shared_ptr<pl::Animation> AnimationManager::addAnimation(
		std::shared_ptr<pl::Slide> slide,
		const pl::Animation::CreateInfo &createInfos
	)
	{
		return this->addAnimation(slide, pl::AnimationManager::s_createAnimation(createInfos));
	}



	std::shared_ptr<pl::Animation> AnimationManager::addAnimation(
		std::shared_ptr<pl::Slide> slide,
		std::shared_ptr<pl::Animation> animation
	)
	{
		m_animations[slide].push_back(animation);
		if (m_animations[slide].size() == 1)
			m_nextAnimation[slide] = m_animations[slide].begin();

		return animation;
	}



	std::shared_ptr<pl::Animation> AnimationManager::s_createAnimation(const pl::Animation::CreateInfo &createInfo)
	{
		switch (createInfo.type)
		{
			case pl::Animation::Type::motion:
				switch (createInfo.interpolationFunction)
				{
					case pl::Animation::InterpolationFunction::linear:
					{
						auto animation {std::make_shared<pl::animations::LinearMotion> (
							std::any_cast<pl::animations::LinearMotion::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeIn:
					{
						auto animation {std::make_shared<pl::animations::EaseInMotion> (
							std::any_cast<pl::animations::EaseInMotion::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeOut:
					{
						auto animation {std::make_shared<pl::animations::EaseOutMotion> (
							std::any_cast<pl::animations::EaseOutMotion::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeInOut:
					{
						auto animation {std::make_shared<pl::animations::EaseInOutMotion> (
							std::any_cast<pl::animations::EaseInOutMotion::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					default:
						throw std::invalid_argument("PL : Invalid given interpolation function");
				}
				break;

			case pl::Animation::Type::rotation:
				switch (createInfo.interpolationFunction)
				{
					case pl::Animation::InterpolationFunction::linear:
					{
						auto animation {std::make_shared<pl::animations::LinearRotation> (
							std::any_cast<pl::animations::LinearRotation::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeIn:
					{
						auto animation {std::make_shared<pl::animations::EaseInRotation> (
							std::any_cast<pl::animations::EaseInRotation::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeOut:
					{
						auto animation {std::make_shared<pl::animations::EaseOutRotation> (
							std::any_cast<pl::animations::EaseOutRotation::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					case pl::Animation::InterpolationFunction::easeInOut:
					{
						auto animation {std::make_shared<pl::animations::EaseInOutRotation> (
							std::any_cast<pl::animations::EaseInOutRotation::CreateInfo> (createInfo.data)
						)};
						animation->setStartFlag(createInfo.startFlag);
						animation->setDuration(createInfo.duration);
						return animation;
					}

					default:
						throw std::invalid_argument("PL : Invalid given interpolation function");
				}
				break;

			default:
				throw std::invalid_argument("PL : Invalid given animations type");
		}

		return std::shared_ptr<pl::Animation> (nullptr);
	}



} // namespace pl
