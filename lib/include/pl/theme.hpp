#pragma once

#include "style.hpp"


namespace pl
{
	class Theme
	{
		public:
			Theme();
			virtual ~Theme() = default;

			pl::Style style;
	};


	inline const pl::Theme &defaultTheme();

} // namespace pl

#include "theme.inl"