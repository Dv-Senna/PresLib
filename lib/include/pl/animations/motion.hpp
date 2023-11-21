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

			void launch() noexcept override;
			void skipToEnd() override;
			void goToStart() override;

			virtual void run(pl::utils::Millisecond dt) override = 0;


		protected:
			pl::animations::Motion::CreateInfo m_generalMotionCreateInfo;
			pl::utils::Millisecond m_totalRunTime;
	};



	class LinearMotion final : public pl::animations::Motion
	{
		public:
			using CreateInfo = pl::animations::Motion::CreateInfo;

			LinearMotion(const pl::animations::LinearMotion::CreateInfo &createInfo);
			~LinearMotion() override = default;

			void run(pl::utils::Millisecond dt) override;
	};



	class EaseInMotion final : public pl::animations::Motion
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithPosition *block;
				glm::vec2 endPosition;
				float strength {0.2f};
				glm::vec2 startPosition {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			EaseInMotion(const pl::animations::EaseInMotion::CreateInfo &createInfo);
			~EaseInMotion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInMotion::CreateInfo m_createInfo;
	};



	class EaseOutMotion final : public pl::animations::Motion
	{
		public:
			using CreateInfo = pl::animations::EaseInMotion::CreateInfo;

			EaseOutMotion(const pl::animations::EaseOutMotion::CreateInfo &createInfo);
			~EaseOutMotion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInMotion::CreateInfo m_createInfo;
	};



	class EaseInOutMotion final : public pl::animations::Motion
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithPosition *block;
				glm::vec2 endPosition;
				float strengthIn {0.2f};
				float strengthOut {0.2};
				glm::vec2 startPosition {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			EaseInOutMotion(const pl::animations::EaseInOutMotion::CreateInfo &createInfo);
			~EaseInOutMotion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInOutMotion::CreateInfo m_createInfo;
	};



} // namespace pl::animations
