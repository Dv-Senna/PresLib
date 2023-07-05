#include "theme.hpp"



namespace pl
{
	Theme::Theme() : 
		style {}
	{
		style.background = nullptr;
		style.foreground = nullptr;
		style.textColor = pl::utils::white;
		style.titleColor = style.textColor;
		style.objectColor = pl::utils::orange;
		style.backgroundColor = pl::utils::black;
		style.mainColor = style.objectColor;
		style.secondColor = style.textColor;
		style.thirdColor = style.backgroundColor;
		style.titlePosition = {20, 20};
		style.titleSize = 25;
		style.titleFont = "";
	}

} // namespace pl
