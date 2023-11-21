#pragma once

#include <any>

#include "utils/types.hpp"



namespace pl
{
	class Animation
	{
		public:
			enum class StartFlag
			{
				withPrevious,
				onNext
			};

			enum class InterpolationFunction
			{
				linear,
				easeIn,
				easeOut,
				easeInOut
			};

			enum class Type
			{
				motion,
				rotation,
				scaling
			};

			struct CreateInfo
			{
				pl::Animation::Type type;
				pl::utils::Second duration;
				pl::Animation::InterpolationFunction interpolationFunction;
				pl::Animation::StartFlag startFlag;
				std::any data;
			};


			Animation();
			Animation(pl::Animation::StartFlag startFlag, pl::utils::Second duration);
			virtual ~Animation() = default;

			virtual void launch() noexcept;
			bool isRunning() const noexcept;
			pl::Animation::StartFlag getStartFlag() const noexcept;
			void setStartFlag(pl::Animation::StartFlag startFlag) noexcept;
			pl::utils::Second getDuration() const noexcept;
			void setDuration(pl::utils::Second duration);

			virtual void run(pl::utils::Millisecond dt) = 0;
			virtual void skipToEnd() = 0;
			virtual void goToStart() = 0;


		protected:
			bool m_isRunning;
			pl::Animation::StartFlag m_startFlag;
			pl::utils::Second m_duration;
	};

} // namespace pl
