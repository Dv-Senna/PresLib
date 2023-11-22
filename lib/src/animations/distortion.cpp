#include <iostream>

#include "animations/distortion.hpp"
#include "utils/function.hpp"



namespace pl::animations
{
	Distortion::Distortion(const pl::animations::Distortion::CreateInfo &createInfo) : 
		pl::Animation(),
		m_generalDistortionCreateInfo {createInfo},
		m_totalRunTime {0.f}
	{
		if (m_generalDistortionCreateInfo.block == nullptr)
			throw std::invalid_argument("PL : Can't set block of Distortion animation to nullptr");
	}



	void Distortion::launch() noexcept
	{
		if (m_generalDistortionCreateInfo.startDistortion == glm::mat4(std::numeric_limits<float>::max()))
			m_generalDistortionCreateInfo.startDistortion = {m_generalDistortionCreateInfo.block->getDistortion()};

		m_totalRunTime = 0.f;
		pl::Animation::launch();
	}



	void Distortion::skipToEnd()
	{
		m_generalDistortionCreateInfo.block->setDistortion(m_generalDistortionCreateInfo.endDistortion);
		m_isRunning = false;
	}



	void Distortion::goToStart()
	{
		m_generalDistortionCreateInfo.block->setDistortion(m_generalDistortionCreateInfo.startDistortion);
		m_isRunning = false;
	}



	LinearDistortion::LinearDistortion(const pl::animations::LinearDistortion::CreateInfo &createInfo) : 
		pl::animations::Distortion(createInfo)
	{

	}


	
	void LinearDistortion::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalDistortionCreateInfo.block->setDistortion(pl::utils::linear(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalDistortionCreateInfo.startDistortion,
			m_generalDistortionCreateInfo.endDistortion
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInDistortion::EaseInDistortion(const pl::animations::EaseInDistortion::CreateInfo &createInfo) : 
		pl::animations::Distortion({createInfo.block, createInfo.endDistortion, createInfo.startDistortion}),
		m_createInfo {createInfo}
	{

	}



	void EaseInDistortion::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalDistortionCreateInfo.block->setDistortion(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalDistortionCreateInfo.startDistortion,
			m_generalDistortionCreateInfo.startDistortion * (1.f - m_createInfo.strength)
			+ m_generalDistortionCreateInfo.endDistortion * m_createInfo.strength,
			m_generalDistortionCreateInfo.endDistortion
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseOutDistortion::EaseOutDistortion(const pl::animations::EaseOutDistortion::CreateInfo &createInfo) : 
		pl::animations::Distortion({createInfo.block, createInfo.endDistortion, createInfo.startDistortion}),
		m_createInfo {createInfo}
	{

	}



	void EaseOutDistortion::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalDistortionCreateInfo.block->setDistortion(pl::utils::quadraticBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalDistortionCreateInfo.startDistortion,
			m_generalDistortionCreateInfo.endDistortion * (1.f - m_createInfo.strength)
			+ m_generalDistortionCreateInfo.startDistortion * m_createInfo.strength,
			m_generalDistortionCreateInfo.endDistortion
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



	EaseInOutDistortion::EaseInOutDistortion(const pl::animations::EaseInOutDistortion::CreateInfo &createInfo) : 
		pl::animations::Distortion({createInfo.block, createInfo.endDistortion, createInfo.startDistortion}),
		m_createInfo {createInfo}
	{

	}



	void EaseInOutDistortion::run(pl::utils::Millisecond dt)
	{
		if (m_duration == 0)
			return this->skipToEnd();

		m_totalRunTime += dt;
		m_generalDistortionCreateInfo.block->setDistortion(pl::utils::cubicBezier(
			m_totalRunTime / (m_duration * 1000.f),
			m_generalDistortionCreateInfo.startDistortion,
			m_generalDistortionCreateInfo.startDistortion * (1.f - m_createInfo.strengthIn)
			+ m_generalDistortionCreateInfo.endDistortion * m_createInfo.strengthIn,
			m_generalDistortionCreateInfo.endDistortion * (1.f - m_createInfo.strengthIn)
			+ m_generalDistortionCreateInfo.startDistortion * m_createInfo.strengthIn,
			m_generalDistortionCreateInfo.endDistortion
		));

		if (m_totalRunTime >= (m_duration * 1000.f))
			this->skipToEnd();
	}



} // namespace pl::animations
