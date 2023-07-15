#pragma once

#include <array>
#include <memory>

#include "../blocks/group.hpp"
#include "../blocks/rectangle.hpp"
#include "../blocks/triangle.hpp"
#include "../theme.hpp"


namespace pl::themes
{
	template <pl::GraphicsApi API>
	class Modern final : public pl::Theme
	{
		public:
			Modern(pl::Instance<API> &instance);
			~Modern();


		private:
			std::unique_ptr<pl::blocks::Group<API>> m_background;
			std::array<std::unique_ptr<pl::blocks::Triangle<API>>, 3> m_backgroundTriangles;
			std::array<std::unique_ptr<pl::blocks::Rectangle<API, pl::args::Color>>, 2> m_titleRectangles;
	};

} // namespace pl::themes


#include "modern.inl"