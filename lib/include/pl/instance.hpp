#pragma once

#include "graphicsApi.inl"
#include "impl/instance.hpp"
#include "slide.hpp"


namespace pl
{
	template <pl::GraphicsApi API>
	class Block;
	

	template <pl::GraphicsApi API>
	class Instance final
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance();
			~Instance();

			inline void run();
			inline std::any getHandler() const noexcept;

			inline void setRenderingCallback(pl::impl::Instance::RenderingCallback callback) noexcept;

			inline std::any getWindow() const noexcept;
			inline const pl::utils::WindowInfos &getWindowInfos() const noexcept;
			inline pl::impl::Instance *getImplementation() const noexcept;

			inline void addSlide(pl::Slide *slide);


		private:
			pl::impl::Instance *m_impl;
	};

} // namespace pl


#include "instance.inl"