#pragma once

#include <limits>

#include "../animation.hpp"
#include "../block.hpp"



namespace pl::animations
{
	class Rotation : public pl::Animation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithOrientation *block;
				pl::utils::Radians endAngle;
				pl::utils::Radians startAngle {std::numeric_limits<float>::max()};
			};

			Rotation(const pl::animations::Rotation::CreateInfo &createInfo);
			virtual ~Rotation() override = default;

			void launch() noexcept override;
			void skipToEnd() override;
			void goToStart() override;

			virtual void run(pl::utils::Millisecond dt) override = 0;


		protected:
			pl::animations::Rotation::CreateInfo m_generalRotationCreateInfo;
			pl::utils::Millisecond m_totalRunTime;
	};



	class LinearRotation final : public pl::animations::Rotation
	{
		public:
			using CreateInfo = pl::animations::Rotation::CreateInfo;

			LinearRotation(const pl::animations::LinearRotation::CreateInfo &createInfo);
			~LinearRotation() override = default;

			void run(pl::utils::Millisecond dt) override;
	};



	class EaseInRotation final : public pl::animations::Rotation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithOrientation *block;
				pl::utils::Radians endAngle;
				float strength {0.2f};
				pl::utils::Radians startAngle {std::numeric_limits<float>::max()};
			};

			EaseInRotation(const pl::animations::EaseInRotation::CreateInfo &createInfo);
			~EaseInRotation() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInRotation::CreateInfo m_createInfo;
	};



	class EaseOutRotation final : public pl::animations::Rotation
	{
		public:
			using CreateInfo = pl::animations::EaseInRotation::CreateInfo;

			EaseOutRotation(const pl::animations::EaseOutRotation::CreateInfo &createInfo);
			~EaseOutRotation() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInRotation::CreateInfo m_createInfo;
	};



	class EaseInOutRotation final : public pl::animations::Rotation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithOrientation *block;
				pl::utils::Radians endAngle;
				float strengthIn {0.2f};
				float strengthOut {0.2};
				pl::utils::Radians startAngle {std::numeric_limits<float>::max()};
			};

			EaseInOutRotation(const pl::animations::EaseInOutRotation::CreateInfo &createInfo);
			~EaseInOutRotation() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInOutRotation::CreateInfo m_createInfo;
	};



} // namespace pl::animations
