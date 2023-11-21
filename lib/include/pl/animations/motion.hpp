#pragma once

#include <limits>

#include "../animation.hpp"
#include "../block.hpp"



namespace pl::animations
{
	class Motion : public pl::Animation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithPosition *block;
				glm::vec2 endPosition;
				glm::vec2 startPosition {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			Motion(const pl::animations::Motion::CreateInfo &createInfo);
			virtual ~Motion() override = default;

			virtual void launch() noexcept override;
			void skipToEnd() override;
			void goToStart() override;

			virtual void run(pl::Millisecond dt) override = 0;


		protected:
			pl::animations::Motion::CreateInfo m_generalMotionCreateInfo;
	};



	class LinearMotion final : public pl::animations::Motion
	{
		public:
			using CreateInfo = pl::animations::Motion::CreateInfo;

			LinearMotion(const pl::animations::LinearMotion::CreateInfo &createInfo);
			~LinearMotion() override = default;

			void launch() noexcept override;
			void run(pl::Millisecond dt) override;


		private:
			glm::vec2 m_slope;
			pl::Millisecond m_totalRunTime;
	};

} // namespace pl::animations
