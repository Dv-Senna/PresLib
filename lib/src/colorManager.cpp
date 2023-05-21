#include "colorManager.hpp"



namespace pl
{
	ColorManager::ColorManager() : m_colors {}, m_scheme {pl::defaultColorScheme}
	{

	}



	void ColorManager::addColor(const std::string &name, const pl::utils::Color &color)
	{
		m_colors[name] = color;
	}



	pl::utils::Color ColorManager::getColor(const std::string &name)
	{
		auto color {m_colors.find(name)};
		if (color == m_colors.end())
			return pl::utils::colorUndefined;

		return color->second;
	}




} // namespace pl