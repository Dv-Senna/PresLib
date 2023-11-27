#include "transition.hpp"



namespace pl
{
	Transition::Transition(const pl::Transition::CreateInfo &createInfo, const glm::vec2 &viewportSize) : 
		m_createInfo {createInfo},
		m_isRunning {false},
		m_totalRunTime {0.f},
		m_viewportSize {viewportSize}
	{

	}



	void Transition::stop()
	{
		m_isRunning = false;
	}



	void Transition::launch()
	{
		m_isRunning = true;
		m_totalRunTime = 0.f;
	}



	bool Transition::isRunning() const noexcept
	{
		return m_isRunning;
	}



} // namespace pl
