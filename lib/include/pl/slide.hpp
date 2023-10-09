#pragma once

#include "graphicsApi.inl"
#include "instance.hpp"
#include "impl/slide.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Slide
	{
		public:
			inline Slide(pl::Instance<API> &instance);
			virtual ~Slide() = default;

			inline void draw();

			inline pl::impl::Slide *getImplementation() noexcept;
			inline pl::Instance<API> &getInstance() noexcept;


		protected:
			pl::impl::Slide m_impl;
			pl::Instance<API> &m_instance;
	};



} // namespace pl


#include "slide.inl"