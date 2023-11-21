#include <iostream>

#include "animations/motion.hpp"



namespace pl::animations
{
	Motion::Motion(const pl::animations::Motion::CreateInfo &createInfo) : 
		pl::Animation(),
		m_generalMotionCreateInfo {createInfo}
	{
		if (m_generalMotionCreateInfo.block == nullptr)
			throw std::invalid_argument("PL : Can't set block of motion animation to nullptr");
	}



	void Motion::launch() noexcept
	{
		if (m_generalMotionCreateInfo.startPosition == glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()))
			m_generalMotionCreateInfo.startPosition = {m_generalMotionCreateInfo.block->getPosition()};

		pl::Animation::launch();
	}



	void Motion::skipToEnd()
	{
		m_generalMotionCreateInfo.block->setPosition(m_generalMotionCreateInfo.endPosition);
		m_isRunning = false;
	}



	void Motion::goToStart()
	{
		m_generalMotionCreateInfo.block->setPosition(m_generalMotionCreateInfo.startPosition);
		m_isRunning = false;
	}



	LinearMotion::LinearMotion(const pl::animations::LinearMotion::CreateInfo &createInfo) : 
		pl::animations::Motion(createInfo),
		m_slope {0, 0},
		m_totalRunTime {0.f}
	{

	}


	
	void LinearMotion::launch() noexcept
	{
		pl::animations::Motion::launch();

		if (m_duration == 0)
		{
			m_slope = {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			return;
		}

		m_slope = (m_generalMotionCreateInfo.endPosition - m_generalMotionCreateInfo.startPosition) / (m_duration * 1000.f);
		m_totalRunTime = 0.f;
	}


	
	void LinearMotion::run(pl::Millisecond dt)
	{
		if (m_slope == glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()))
			return this->skipToEnd();

		m_generalMotionCreateInfo.block->setPosition(m_generalMotionCreateInfo.block->getPosition() + m_slope * dt);
		m_totalRunTime += dt;

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}


	
} // namespace pl::animations
