#pragma once

#include <string>
#include <unordered_map>

#include "font.hpp"


namespace pl
{
	class FontManager final
	{
		public:
			FontManager();
			~FontManager();

			void add(const std::string &name, const std::string &path);
			TTF_Font *get(const std::string &name, int size);


		private:
			std::unordered_map<std::string, std::string> m_registereds;
			std::unordered_map<std::string, std::unordered_map<int, pl::Font*>> m_fonts;
	};

} // namespace pl
