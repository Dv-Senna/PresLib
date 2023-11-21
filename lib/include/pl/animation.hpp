#pragma once

#include <any>



namespace pl
{
	using Second = float;
	using Millisecond = float;

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
				linear
			};

			enum class Type
			{
				motion
			};

			struct CreateInfo
			{
				pl::Animation::Type type;
				pl::Second duration;
				pl::Animation::InterpolationFunction interpolationFunction;
				pl::Animation::StartFlag startFlag;
				std::any data;
			};


			Animation();
			Animation(pl::Animation::StartFlag startFlag, pl::Second duration);
			virtual ~Animation() = default;

			virtual void launch() noexcept;
			bool isRunning() const noexcept;
			pl::Animation::StartFlag getStartFlag() const noexcept;
			void setStartFlag(pl::Animation::StartFlag startFlag) noexcept;
			pl::Second getDuration() const noexcept;
			void setDuration(pl::Second duration);

			virtual void run(pl::Millisecond dt) = 0;
			virtual void skipToEnd() = 0;
			virtual void goToStart() = 0;


		protected:
			bool m_isRunning;
			pl::Animation::StartFlag m_startFlag;
			pl::Second m_duration;
	};

} // namespace pl
