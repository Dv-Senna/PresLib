#pragma once

#include <list>


namespace pl::impl {class Slide;}


namespace pl::impl::manager
{
	class Event;

	class Slide final
	{
		public:
			Slide();
			~Slide() = default;

			void add(pl::impl::Slide *slide);
			void draw();
			bool process(pl::impl::manager::Event *eventManager);


		private:
			std::list<pl::impl::Slide*> m_slides;
			std::list<pl::impl::Slide*>::iterator m_currentSlide;
			
	};



} // namespace pl::impl::manager
