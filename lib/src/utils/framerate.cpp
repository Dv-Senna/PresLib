#include <thread>

#include <SDL2/SDL.h>

#include "utils/framerate.hpp"



namespace pl::utils
{
	FPSManager::FPSManager(int targetedFPS) :
		m_clock {std::chrono::steady_clock::now()},
		m_targetedRenderTime {1000.0 / static_cast<double> (targetedFPS)},
		m_lastRenderTime {}
	{
		
	}



	void FPSManager::cap()
	{
		auto current = std::chrono::steady_clock::now();
		auto interval = std::chrono::duration_cast<pl::utils::FPSManager::Milliseconds> (current - m_clock);

		if (interval.count() < m_targetedRenderTime.count())
			SDL_Delay((m_targetedRenderTime - interval).count());

		m_lastRenderTime = std::chrono::steady_clock::now() - m_clock;
		m_clock = std::chrono::steady_clock::now();
	}



	pl::utils::FPSManager::Milliseconds FPSManager::getLastFrameRenderTime() const noexcept
	{
		return m_lastRenderTime;
	}



} // namespace pl::utils
