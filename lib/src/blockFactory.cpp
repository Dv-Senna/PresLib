#include "pl/blockFactory.hpp"



namespace pl {
	BlockFactory::BlockFactory(const pl::BlockFactory::CreateInfos &createInfos) :
		m_heapAllocator {{
			.size = createInfos.heapSize
		}},
		m_memoryManager {{
			.allocator = &m_heapAllocator
		}}
	{

	}


	BlockFactory::~BlockFactory() {

	}


} // namespace pl
