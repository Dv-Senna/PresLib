#pragma once

#include "../transition.hpp"
#include "../utils/types.hpp"



namespace pl::transitions
{
	class Fade final : public pl::Transition
	{
		public:
			struct CreateInfo
			{
				pl::utils::Color colorShift {pl::utils::black};
			};

			Fade(const pl::Transition::CreateInfo &createInfo, const glm::vec2 &viewportSize);
			~Fade() override = default;

			void launch() override;
			void run(
				pl::utils::Millisecond dt,
				glm::mat4 &oldSlide,
				glm::mat4 &nextSlide,
				pl::utils::Color &oldColor,
				pl::utils::Color &nextColor
			) override;


		private:
			pl::transitions::Fade::CreateInfo m_specificCreateInfo;
	};
} // namespace pl::transitions
