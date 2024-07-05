#pragma once

#include "pl/core.hpp"
#include "pl/memory/allocator.hpp"



namespace pl::memory {
	class PL_CORE Manager final {
		public:
			struct CreateInfos {
				pl::memory::Allocator *allocator;
			};

			Manager(const pl::memory::Manager::CreateInfos &createInfos);
			~Manager();

			template <typename T, typename ...Args>
			T *allocate(Args ...args);

			template <typename T>
			void free(T *ptr);

			inline void setAllocator(pl::memory::Allocator *allocator) noexcept;
			inline pl::memory::Allocator *setAllocator() const noexcept;


		private:
			pl::memory::Allocator *m_allocator;
			pl::Count m_allocationCount;
	};

} // namespace pl::memory


#include "pl/memory/manager.hpp"