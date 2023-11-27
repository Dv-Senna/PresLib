#pragma once

#include "../transition.hpp"
#include "../utils/types.hpp"



namespace pl::transitions
{
	class SlideTogether final : public pl::Transition
	{
		public:
			struct CreateInfo
			{
				pl::utils::Axis axis {pl::utils::Axis::x};
				float spaceBetweenSlides {2.f};
			};

			SlideTogether(const pl::Transition::CreateInfo &createInfo, const glm::vec2 &viewportSize);
			~SlideTogether() override = default;

			void launch() override;
			void run(
				pl::utils::Millisecond dt,
				glm::mat4 &oldSlide,
				glm::mat4 &nextSlide,
				pl::utils::Color &oldColor,
				pl::utils::Color &nextColor
			) override;


		private:
			pl::transitions::SlideTogether::CreateInfo m_specificCreateInfo;
	};
} // namespace pl::transitions
