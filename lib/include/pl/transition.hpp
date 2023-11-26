#pragma once

#include <any>

#include <glm/glm.hpp>

#include "utils/types.hpp"



namespace pl
{
	class Transition
	{
		public:
			enum class StartFlag
			{
				withPrevious,
				onNext
			};

			struct CreateInfo
			{
				pl::utils::Second duration;
				std::any data {};
				pl::utils::Second delay {0.f};
				pl::Transition::StartFlag startFlag {pl::Transition::StartFlag::onNext};
			};

			Transition(const pl::Transition::CreateInfo &createInfo);
			virtual ~Transition() = default;

			void stop();
			virtual void launch();
			virtual void run(pl::utils::Millisecond dt, glm::mat4 &oldSlide, glm::mat4 &nextSlide) = 0;

			bool isRunning() const noexcept;


		protected:
			pl::Transition::CreateInfo m_createInfo;
			bool m_isRunning;
			pl::utils::Millisecond m_totalRunTime;
	};

} // namespace pl
