#include "pl/resourceManager.hpp"

#include "pl/instance.hpp"



namespace pl {
	void ResourceManager::create(const pl::ResourceManager::CreateInfos &createInfos) {
		s_instance = createInfos.instance;

		pl::memory::HeapAllocator::CreateInfos heapAllocatorCreateInfos {};
		heapAllocatorCreateInfos.size = createInfos.heapSize;
		s_heapAllocator = s_instance->allocateObject<pl::memory::HeapAllocator> (heapAllocatorCreateInfos);

		pl::memory::Manager::CreateInfos memoryManagerCreateInfos {};
		memoryManagerCreateInfos.allocator = s_heapAllocator;
		s_memoryManager = s_instance->allocateObject<pl::memory::Manager> (memoryManagerCreateInfos);
	}


	void ResourceManager::destroy() {
		s_instance->freeObject(s_memoryManager);
		s_instance->freeObject(s_heapAllocator);
	}


	pl::Instance *s_instance {nullptr};
	pl::memory::HeapAllocator *ResourceManager::s_heapAllocator {nullptr};
	pl::memory::Manager *ResourceManager::s_memoryManager {nullptr};

} // namespace pl
