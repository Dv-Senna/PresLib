#pragma once

#include <string>
#include <unordered_map>

#include "utils/color.hpp"


namespace pl
{
	struct ColorScheme
	{
		pl::utils::Color text, title, object, background;
	};


	inline const pl::ColorScheme defaultColorScheme {
		.text={0, 0, 0},
		.title={0, 0, 0},
		.object={255, 130, 0},
		.background={255, 255, 255}
	};


	class ColorManager
	{
		public:
			ColorManager();
			~ColorManager() = default;

			void addColor(const std::string &name, const pl::utils::Color &color);

			pl::utils::Color getColor(const std::string &name);
			inline const pl::ColorScheme &getScheme() const noexcept {return m_scheme;} 

			inline void setScheme(const pl::ColorScheme &scheme) {m_scheme = scheme;}

		
		private:
			std::unordered_map<std::string, pl::utils::Color> m_colors;
			pl::ColorScheme m_scheme;
	};

} // namespace pl