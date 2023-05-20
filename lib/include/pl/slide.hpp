#pragma once

#include <list>


namespace pl
{
	class Block;

	/// @brief A class that handle slide
	class Slide final
	{
		public:
			Slide();
			~Slide() = default;

			void render();

			void addChildren(pl::Block *block);
			void removeChildren(pl::Block *block);


		private:
			std::list<pl::Block *> m_blocks;
	};


} // namespace pl
