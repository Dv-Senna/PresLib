#include "transition.hpp"



namespace pl
{
	Transition::Transition(const pl::Transition::CreateInfo &createInfo) : 
		m_createInfo {createInfo},
		m_isRunning {false},
		m_totalRunTime {0.f}
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
