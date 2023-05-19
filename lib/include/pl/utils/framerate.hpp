#pragma once

#include <chrono>


namespace pl::utils
{
	class FPSManager final
	{
		using Milliseconds = std::chrono::duration<double, std::milli>;

		public:
			FPSManager(int targetedFPS);
			~FPSManager() = default;

			void cap();

			pl::utils::FPSManager::Milliseconds getLastFrameRenderTime() const noexcept;

		private:
			std::chrono::time_point<std::chrono::steady_clock> m_clock;
			pl::utils::FPSManager::Milliseconds m_targetedRenderTime, m_lastRenderTime;
	};

} // namespace pl::utils
