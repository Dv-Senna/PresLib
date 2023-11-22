#include "animation.hpp"



namespace pl
{
	Animation::Animation() : 
		m_isRunning {false},
		m_startFlag {pl::Animation::StartFlag::withPrevious},
		m_duration {0.f}
	{

	}



	Animation::Animation(pl::Animation::StartFlag startFlag, pl::utils::Second duration) :
		m_isRunning {false},
		m_startFlag {startFlag},
		m_duration {duration}
	{

	}



	void Animation::launch() noexcept
	{
		m_isRunning = true;
	}



	bool Animation::isRunning() const noexcept
	{
		return m_isRunning;
	}



	pl::Animation::StartFlag Animation::getStartFlag() const noexcept
	{
		return m_startFlag;
	}



	void Animation::setStartFlag(pl::Animation::StartFlag startFlag) noexcept
	{
		m_startFlag = startFlag;
	}



	pl::utils::Second Animation::getDuration() const noexcept
	{
		return m_duration;
	}



	void Animation::setDuration(pl::utils::Second duration)
	{
		m_duration = duration;
	}



} // namespace pl
