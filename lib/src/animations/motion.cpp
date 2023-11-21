#include <iostream>

#include "animations/motion.hpp"
#include "utils/function.hpp"



namespace pl::animations
{
	Motion::Motion(const pl::animations::Motion::CreateInfo &createInfo) : 
		pl::Animation(),
		m_generalMotionCreateInfo {createInfo},
		m_totalRunTime {0.f}
	{
		if (m_generalMotionCreateInfo.block == nullptr)
			throw std::invalid_argument("PL : Can't set block of motion animation to nullptr");
	}



	void Motion::launch() noexcept
	{
		if (m_generalMotionCreateInfo.startPosition == glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()))
			m_generalMotionCreateInfo.startPosition = {m_generalMotionCreateInfo.block->getPosition()};

		m_totalRunTime = 0.f;
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
		pl::animations::Motion(createInfo)
	{

	}


	
	void LinearMotion::run(pl::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalMotionCreateInfo.block->setPosition(pl::utils::linear(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalMotionCreateInfo.startPosition,
			m_generalMotionCreateInfo.endPosition
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInMotion::EaseInMotion(const pl::animations::EaseInMotion::CreateInfo &createInfo) : 
		pl::animations::Motion({createInfo.block, createInfo.endPosition, createInfo.startPosition}),
		m_createInfo {createInfo}
	{

	}



	void EaseInMotion::run(pl::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalMotionCreateInfo.block->setPosition(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalMotionCreateInfo.startPosition,
			m_generalMotionCreateInfo.startPosition * (1.f - m_createInfo.strength)
			+ m_generalMotionCreateInfo.endPosition * m_createInfo.strength,
			m_generalMotionCreateInfo.endPosition
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseOutMotion::EaseOutMotion(const pl::animations::EaseOutMotion::CreateInfo &createInfo) : 
		pl::animations::Motion({createInfo.block, createInfo.endPosition, createInfo.startPosition}),
		m_createInfo {createInfo}
	{

	}



	void EaseOutMotion::run(pl::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalMotionCreateInfo.block->setPosition(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalMotionCreateInfo.startPosition,
			m_generalMotionCreateInfo.endPosition * (1.f - m_createInfo.strength)
			+ m_generalMotionCreateInfo.startPosition * m_createInfo.strength,
			m_generalMotionCreateInfo.endPosition
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInOutMotion::EaseInOutMotion(const pl::animations::EaseInOutMotion::CreateInfo &createInfo) : 
		pl::animations::Motion({createInfo.block, createInfo.endPosition, createInfo.startPosition}),
		m_createInfo {createInfo}
	{

	}



	void EaseInOutMotion::run(pl::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalMotionCreateInfo.block->setPosition(pl::utils::cubicBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalMotionCreateInfo.startPosition,
			m_generalMotionCreateInfo.startPosition * (1.f - m_createInfo.strengthIn)
			+ m_generalMotionCreateInfo.endPosition * m_createInfo.strengthIn,
			m_generalMotionCreateInfo.endPosition * (1.f - m_createInfo.strengthIn)
			+ m_generalMotionCreateInfo.startPosition * m_createInfo.strengthIn,
			m_generalMotionCreateInfo.endPosition
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



} // namespace pl::animations
