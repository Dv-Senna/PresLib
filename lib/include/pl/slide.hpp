#pragma once

#include <list>
#include <memory>
#include <string>

#include "block/text.hpp"


namespace pl
{
	/// @brief Flag specific to pl::Slide. Add multiple with | operator
	enum class SlideFlag
	{
		none = 0b00000000,
		no_overlay = 0b00000001,
		no_background = 0b00000010,
	};

	inline pl::SlideFlag operator&(pl::SlideFlag flag1, pl::SlideFlag flag2)
	{
		return static_cast<pl::SlideFlag> (static_cast<int>(flag1) & static_cast<int>(flag2));
	}

	inline pl::SlideFlag operator|(pl::SlideFlag flag1, pl::SlideFlag flag2)
	{
		return static_cast<pl::SlideFlag> (static_cast<int>(flag1) | static_cast<int>(flag2));
	}

	inline bool operator!(pl::SlideFlag flags)
	{
		return !static_cast<int> (flags);
	}



	class Block;

	/// @brief A class that handle slide
	class Slide final
	{
		public:
			/// @brief Constructor
			/// @param flags Flags you want to add to the slide separate by | operator
			Slide(pl::Instance &instance, pl::SlideFlag flags = pl::SlideFlag::none);
			~Slide() = default;

			void render();

			void addChildren(pl::Block *block);
			void removeChildren(pl::Block *block);

			void setTitle(const std::string &title);

			inline pl::SlideFlag getFlags() const noexcept {return m_flags;}


		private:
			pl::Instance &m_instance;
			pl::SlideFlag m_flags;
			std::list<pl::Block *> m_blocks;
			std::unique_ptr<pl::block::Text> m_title;
	};


} // namespace pl
