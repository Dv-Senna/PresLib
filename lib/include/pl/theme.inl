#include "theme.hpp"



namespace pl
{
	inline const pl::Theme &defaultTheme()
	{
		static pl::Theme theme {};
		return theme;
	}



} // namespace pl
