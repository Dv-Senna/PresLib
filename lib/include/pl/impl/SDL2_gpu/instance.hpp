#pragma once

#include "../instance.hpp"


namespace pl::impl::SDL2_gpu
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
	};

} // namespace pl::impl::SDL2_gpu


#include "instance.inl"