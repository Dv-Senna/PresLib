#pragma once

#include "instance.hpp"


namespace pl::impl
{
	class Slide
	{
		public:
			Slide(pl::impl::Instance *instance);
			virtual ~Slide() = default;

			void draw();

			inline pl::impl::Instance *getInstance() noexcept;


		private:
			pl::impl::Instance *m_instance;
	};



} // namespace pl::impl


#include "slide.inl"