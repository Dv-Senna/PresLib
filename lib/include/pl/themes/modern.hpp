#pragma once

#include <array>
#include <memory>

#include "../block/rectangle.hpp"
#include "../block/triangle.hpp"
#include "../theme.hpp"


namespace pl::themes
{
	class Modern final : public pl::Theme
	{
		public:
			Modern(pl::Instance &instance);
			~Modern();


		private:
			std::array<std::unique_ptr<pl::block::Triangle>, 3> m_backgroundTriangles;
			std::array<std::unique_ptr<pl::block::Rectangle>, 2> m_titleRectangles;
	};

} // namespace pl::themes