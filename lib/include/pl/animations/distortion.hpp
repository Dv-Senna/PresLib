#pragma once

#include <limits>

#include "../animation.hpp"
#include "../block.hpp"



namespace pl::animations
{
	class Distortion : public pl::Animation
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithDistortion *block;
				glm::mat4 endDistortion;
				glm::mat4 startDistortion {std::numeric_limits<float>::max()};
			};

			Distortion(const pl::animations::Distortion::CreateInfo &createInfo);
			virtual ~Distortion() override = default;

			void launch() noexcept override;
			void skipToEnd() override;
			void goToStart() override;

			virtual void run(pl::utils::Millisecond dt) override = 0;


		protected:
			pl::animations::Distortion::CreateInfo m_generalDistortionCreateInfo;
			pl::utils::Millisecond m_totalRunTime;
	};



	class LinearDistortion final : public pl::animations::Distortion
	{
		public:
			using CreateInfo = pl::animations::Distortion::CreateInfo;

			LinearDistortion(const pl::animations::LinearDistortion::CreateInfo &createInfo);
			~LinearDistortion() override = default;

			void run(pl::utils::Millisecond dt) override;
	};



	class EaseInDistortion final : public pl::animations::Distortion
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithDistortion *block;
				glm::mat4 endDistortion;
				float strength {0.2f};
				glm::mat4 startDistortion {std::numeric_limits<float>::max()};
			};

			EaseInDistortion(const pl::animations::EaseInDistortion::CreateInfo &createInfo);
			~EaseInDistortion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInDistortion::CreateInfo m_createInfo;
	};



	class EaseOutDistortion final : public pl::animations::Distortion
	{
		public:
			using CreateInfo = pl::animations::EaseInDistortion::CreateInfo;

			EaseOutDistortion(const pl::animations::EaseOutDistortion::CreateInfo &createInfo);
			~EaseOutDistortion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInDistortion::CreateInfo m_createInfo;
	};



	class EaseInOutDistortion final : public pl::animations::Distortion
	{
		public:
			struct CreateInfo
			{
				pl::BlockWithDistortion *block;
				glm::mat4 endDistortion;
				float strengthIn {0.2f};
				float strengthOut {0.2};
				glm::mat4 startDistortion {std::numeric_limits<float>::max()};
			};

			EaseInOutDistortion(const pl::animations::EaseInOutDistortion::CreateInfo &createInfo);
			~EaseInOutDistortion() override = default;

			void run(pl::utils::Millisecond dt) override;


		private:
			pl::animations::EaseInOutDistortion::CreateInfo m_createInfo;
	};



} // namespace pl::animations
