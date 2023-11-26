#pragma once

#include "../transition.hpp"



namespace pl::transitions
{
	class SlideTogether final : public pl::Transition
	{
		public:
			SlideTogether(const pl::Transition::CreateInfo &createInfo);
			~SlideTogether() override = default;

			void launch() override;
			void run(pl::utils::Millisecond dt, glm::mat4 &oldSlide, glm::mat4 &nextSlide) override;
	};
} // namespace pl::transitions
