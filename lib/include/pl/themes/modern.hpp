#pragma once

#include "../theme.hpp"


namespace pl::themes
{
	class Modern : public pl::Theme
	{
		public:
			Modern(pl::Instance &instance);
			virtual ~Modern() = default;

			virtual void preRendering();
			virtual void postRendering();
			virtual void registerSlide(std::shared_ptr<pl::Slide> slide, const pl::Slide::CreateInfo &createInfo);


		private:
			
	};

} // namespace pl::themes
