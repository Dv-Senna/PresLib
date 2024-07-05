#pragma once

#include "pl/block.hpp"
#include "pl/concepts.hpp"
#include "pl/core.hpp"
#include "pl/memory/heapAllocator.hpp"
#include "pl/memory/manager.hpp"
#include "pl/reference.hpp"



namespace pl {
	class PL_CORE BlockFactory final {
		public:
			struct CreateInfos {
				pl::ByteCount heapSize;
			};

			BlockFactory(const pl::BlockFactory::CreateInfos &createInfos);
			~BlockFactory();

			template <typename T>
			PL_REQUIRES(pl::concepts::IsBlock<T>)
			pl::Reference<T> create(const typename T::CreateInfos &createInfos);

		private:
			pl::memory::HeapAllocator m_heapAllocator;
			pl::memory::Manager m_memoryManager;

	};

} // namespace pl


#include "pl/blockFactory.inl"