#pragma once

#include "../graphicsApi.inl"
#include "../macros.inl"
#include "../impl/manager/slide.hpp"


namespace pl {template <pl::GraphicsApi API> class Slide;}


namespace pl::manager
{
	template <pl::GraphicsApi API>
	class Event;

	template <pl::GraphicsApi API>
	class Slide final
	{
		public:
			Slide();
			~Slide() = default;

			inline void add(pl::Slide<API> *slide);
			inline void draw();
			inline bool process(pl::manager::Event<API> &eventManager);

			inline pl::impl::manager::Slide *getImplementation() noexcept;
		

		private:
			pl::impl::manager::Slide m_impl;
	};



} // namespace pl::manager


#include "slide.inl"