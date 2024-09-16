#pragma once

#include <vector>

#include "pl/core.hpp"
#include "pl/memory/allocator.hpp"
#include "pl/types.hpp"



namespace pl::memory {
	class PL_CORE HeapAllocator final : public pl::memory::Allocator {
		public:
			struct CreateInfos {
				pl::ByteCount size;
			};

			HeapAllocator(const pl::memory::HeapAllocator::CreateInfos &createInfos);
			~HeapAllocator() override;

			void *allocate(pl::ByteCount size, pl::ByteCount alignement) override;
			void free(void *ptr) noexcept override;

		private:
			bool m_isValid() const noexcept;

			struct Space {
				pl::Byte *start;
				pl::ByteCount size;
			};

			pl::Byte *m_heap;
			pl::ByteCount m_heapSize;
			std::vector<Space> m_freeSpaces;
	};

} // namespace pl::memory
