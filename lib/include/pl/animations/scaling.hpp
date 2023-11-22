#pragma once

#include <limits>

#include "../animation.hpp"
#include "../block.hpp"



namespace pl::animations
{
	class Scaling : public pl::Animation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithSize *block;
				glm::vec2 endSize;
				glm::vec2 startSize {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			Scaling(const pl::animations::Scaling::CreateInfo &createInfo);
			virtual ~Scaling() override = default;

			void launch() noexcept override;
			void skipToEnd() override;
			void goToStart() override;

			virtual void run(pl::utils::Millisecond dt) override = 0;


		protected:
			pl::animations::Scaling::CreateInfo m_generalScalingCreateInfo;
			pl::utils::Millisecond m_totalRunTime;
			glm::vec2 m_startSizeInPixels;
	};



	class LinearScaling final : public pl::animations::Scaling
	{
		public:
			using CreateInfo = pl::animations::Scaling::CreateInfo;

			LinearScaling(const pl::animations::LinearScaling::CreateInfo &createInfo);
			~LinearScaling() override = default;

			void run(pl::utils::Millisecond dt) override;
	};



	class EaseInScaling final : public pl::animations::Scaling
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithSize *block;
				glm::vec2 endSize;
				float strength {0.2f};
				glm::vec2 startSize {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			EaseInScaling(const pl::animations::EaseInScaling::CreateInfo &createInfo);
			~EaseInScaling() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInScaling::CreateInfo m_createInfo;
	};



	class EaseOutScaling final : public pl::animations::Scaling
	{
		public:
			using CreateInfo = pl::animations::EaseInScaling::CreateInfo;

			EaseOutScaling(const pl::animations::EaseOutScaling::CreateInfo &createInfo);
			~EaseOutScaling() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInScaling::CreateInfo m_createInfo;
	};



	class EaseInOutScaling final : public pl::animations::Scaling
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithSize *block;
				glm::vec2 endSize;
				float strengthIn {0.2f};
				float strengthOut {0.2};
				glm::vec2 startSize {std::numeric_limits<float>::max(), std::numeric_limits<float>::max()};
			};

			EaseInOutScaling(const pl::animations::EaseInOutScaling::CreateInfo &createInfo);
			~EaseInOutScaling() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInOutScaling::CreateInfo m_createInfo;
	};



} // namespace pl::animations
