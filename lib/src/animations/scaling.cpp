#include <iostream>

#include "animations/scaling.hpp"
#include "utils/function.hpp"



namespace pl::animations
{
	Scaling::Scaling(const pl::animations::Scaling::CreateInfo &createInfo) : 
		pl::Animation(),
		m_generalScalingCreateInfo {createInfo},
		m_totalRunTime {0.f}
	{
		if (m_generalScalingCreateInfo.block == nullptr)
			throw std::invalid_argument("PL : Can't set block of Scaling animation to nullptr");
	}



	void Scaling::launch() noexcept
	{
		m_startSizeInPixels = m_generalScalingCreateInfo.block->getSize();

		if (m_generalScalingCreateInfo.startSize == glm::vec2(std::numeric_limits<float>::max(), std::numeric_limits<float>::max()))
			m_generalScalingCreateInfo.startSize = {1.f, 1.f};

		m_totalRunTime = 0.f;
		pl::Animation::launch();
	}



	void Scaling::skipToEnd()
	{
		m_generalScalingCreateInfo.block->setSize(m_generalScalingCreateInfo.endSize * m_startSizeInPixels);
		m_isRunning = false;
	}



	void Scaling::goToStart()
	{
		m_generalScalingCreateInfo.block->setSize(m_generalScalingCreateInfo.startSize * m_startSizeInPixels);
		m_isRunning = false;
	}



	LinearScaling::LinearScaling(const pl::animations::LinearScaling::CreateInfo &createInfo) : 
		pl::animations::Scaling(createInfo)
	{

	}


	
	void LinearScaling::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalScalingCreateInfo.block->setSize(pl::utils::linear(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalScalingCreateInfo.startSize,
			m_generalScalingCreateInfo.endSize
		) * m_startSizeInPixels);

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInScaling::EaseInScaling(const pl::animations::EaseInScaling::CreateInfo &createInfo) : 
		pl::animations::Scaling({createInfo.block, createInfo.endSize, createInfo.startSize}),
		m_createInfo {createInfo}
	{

	}



	void EaseInScaling::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalScalingCreateInfo.block->setSize(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalScalingCreateInfo.startSize,
			m_generalScalingCreateInfo.startSize * (1.f - m_createInfo.strength)
			+ m_generalScalingCreateInfo.endSize * m_createInfo.strength,
			m_generalScalingCreateInfo.endSize
		) * m_startSizeInPixels);

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseOutScaling::EaseOutScaling(const pl::animations::EaseOutScaling::CreateInfo &createInfo) : 
		pl::animations::Scaling({createInfo.block, createInfo.endSize, createInfo.startSize}),
		m_createInfo {createInfo}
	{

	}



	void EaseOutScaling::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalScalingCreateInfo.block->setSize(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalScalingCreateInfo.startSize,
			m_generalScalingCreateInfo.endSize * (1.f - m_createInfo.strength)
			+ m_generalScalingCreateInfo.startSize * m_createInfo.strength,
			m_generalScalingCreateInfo.endSize
		) * m_startSizeInPixels);

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInOutScaling::EaseInOutScaling(const pl::animations::EaseInOutScaling::CreateInfo &createInfo) : 
		pl::animations::Scaling({createInfo.block, createInfo.endSize, createInfo.startSize}),
		m_createInfo {createInfo}
	{

	}



	void EaseInOutScaling::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalScalingCreateInfo.block->setSize(pl::utils::cubicBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalScalingCreateInfo.startSize,
			m_generalScalingCreateInfo.startSize * (1.f - m_createInfo.strengthIn)
			+ m_generalScalingCreateInfo.endSize * m_createInfo.strengthIn,
			m_generalScalingCreateInfo.endSize * (1.f - m_createInfo.strengthIn)
			+ m_generalScalingCreateInfo.startSize * m_createInfo.strengthIn,
			m_generalScalingCreateInfo.endSize
		) * m_startSizeInPixels);

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



} // namespace pl::animations
