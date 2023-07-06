#pragma once

#include "../instance.hpp"


namespace pl::impl::SDL2_renderer
{
	class Instance final : public pl::impl::Instance
	{
		public:
			PL_CLASS_NO_COPY_MOVE(Instance);

			Instance();
			virtual ~Instance();

			virtual void run();
			virtual inline std::any getHandler() const noexcept;

		
		private:
			SDL_Renderer *m_handler;
	};

} // namespace pl::impl::SDL2_renderer


#include "instance.inl"