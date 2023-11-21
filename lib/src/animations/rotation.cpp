#include <iostream>

#include "animations/rotation.hpp"
#include "utils/function.hpp"



namespace pl::animations
{
	Rotation::Rotation(const pl::animations::Rotation::CreateInfo &createInfo) : 
		pl::Animation(),
		m_generalRotationCreateInfo {createInfo},
		m_totalRunTime {0.f}
	{
		if (m_generalRotationCreateInfo.block == nullptr)
			throw std::invalid_argument("PL : Can't set block of Rotation animation to nullptr");
	}



	void Rotation::launch() noexcept
	{
		if (m_generalRotationCreateInfo.startAngle == std::numeric_limits<float>::max())
			m_generalRotationCreateInfo.startAngle = {m_generalRotationCreateInfo.block->getOrientation()};

		m_totalRunTime = 0.f;
		pl::Animation::launch();
	}



	void Rotation::skipToEnd()
	{
		m_generalRotationCreateInfo.block->setOrientation(m_generalRotationCreateInfo.endAngle);
		m_isRunning = false;
	}



	void Rotation::goToStart()
	{
		m_generalRotationCreateInfo.block->setOrientation(m_generalRotationCreateInfo.startAngle);
		m_isRunning = false;
	}



	LinearRotation::LinearRotation(const pl::animations::LinearRotation::CreateInfo &createInfo) : 
		pl::animations::Rotation(createInfo)
	{

	}


	
	void LinearRotation::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalRotationCreateInfo.block->setOrientation(pl::utils::linear(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalRotationCreateInfo.startAngle,
			m_generalRotationCreateInfo.endAngle
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInRotation::EaseInRotation(const pl::animations::EaseInRotation::CreateInfo &createInfo) : 
		pl::animations::Rotation({createInfo.block, createInfo.endAngle, createInfo.startAngle}),
		m_createInfo {createInfo}
	{

	}



	void EaseInRotation::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalRotationCreateInfo.block->setOrientation(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalRotationCreateInfo.startAngle,
			m_generalRotationCreateInfo.startAngle * (1.f - m_createInfo.strength)
			+ m_generalRotationCreateInfo.endAngle * m_createInfo.strength,
			m_generalRotationCreateInfo.endAngle
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseOutRotation::EaseOutRotation(const pl::animations::EaseOutRotation::CreateInfo &createInfo) : 
		pl::animations::Rotation({createInfo.block, createInfo.endAngle, createInfo.startAngle}),
		m_createInfo {createInfo}
	{

	}



	void EaseOutRotation::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalRotationCreateInfo.block->setOrientation(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalRotationCreateInfo.startAngle,
			m_generalRotationCreateInfo.endAngle * (1.f - m_createInfo.strength)
			+ m_generalRotationCreateInfo.startAngle * m_createInfo.strength,
			m_generalRotationCreateInfo.endAngle
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInOutRotation::EaseInOutRotation(const pl::animations::EaseInOutRotation::CreateInfo &createInfo) : 
		pl::animations::Rotation({createInfo.block, createInfo.endAngle, createInfo.startAngle}),
		m_createInfo {createInfo}
	{

	}



	void EaseInOutRotation::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalRotationCreateInfo.block->setOrientation(pl::utils::cubicBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalRotationCreateInfo.startAngle,
			m_generalRotationCreateInfo.startAngle * (1.f - m_createInfo.strengthIn)
			+ m_generalRotationCreateInfo.endAngle * m_createInfo.strengthIn,
			m_generalRotationCreateInfo.endAngle * (1.f - m_createInfo.strengthIn)
			+ m_generalRotationCreateInfo.startAngle * m_createInfo.strengthIn,
			m_generalRotationCreateInfo.endAngle
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



} // namespace pl::animations
