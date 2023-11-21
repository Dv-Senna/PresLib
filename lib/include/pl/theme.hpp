#pragma once

#include <memory>

#include "slide.hpp"
#include "style.hpp"


namespace pl
{
	struct Instance;

	class Theme
	{
		public:
			inline Theme(pl::Instance &instance);
			virtual ~Theme() = default;

			virtual void preRendering() = 0;
			virtual void postRendering() = 0;
			virtual void registerSlide(std::shared_ptr<pl::Slide> slide, const pl::Slide::CreateInfo &createInfo) = 0;

			inline const pl::Style &getStyle() const noexcept;


		protected:
			pl::Instance &m_instance;
			pl::Style m_style;
	};

} // namespace pl


#include "theme.inl"