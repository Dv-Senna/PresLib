#pragma once

#include <any>

#include <glm/glm.hpp>

#include "utils/color.hpp"
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

			Transition(const pl::Transition::CreateInfo &createInfo, const glm::vec2 &viewportSize);
			virtual ~Transition() = default;

			void stop();
			virtual void launch();
			virtual void run(
				pl::utils::Millisecond dt,
				glm::mat4 &oldSlide,
				glm::mat4 &nextSlide,
				pl::utils::Color &oldColor,
				pl::utils::Color &nextColor
			) = 0;

			bool isRunning() const noexcept;


		protected:
			pl::Transition::CreateInfo m_createInfo;
			bool m_isRunning;
			pl::utils::Millisecond m_totalRunTime;
			glm::vec2 m_viewportSize;
	};

} // namespace pl
