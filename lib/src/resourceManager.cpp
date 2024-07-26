#include "pl/resourceManager.hpp"

#include "pl/image.hpp"
#include "pl/instance.hpp"



namespace pl {
	template <>
	pl::Resource<pl::Image> ResourceManager::load<pl::Image, std::filesystem::path> (const std::filesystem::path &path) {
		pl::Resource<pl::Image> resource {s_memoryManager->allocate<pl::Image> (path)};
		return resource;
	}


	template <>
	void ResourceManager::unload<pl::Image> (const pl::Resource<pl::Image> &resource) {
		s_memoryManager->free(resource.m_ptr);
	}


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


	pl::Instance *ResourceManager::s_instance {nullptr};
	pl::memory::HeapAllocator *ResourceManager::s_heapAllocator {nullptr};
	pl::memory::Manager *ResourceManager::s_memoryManager {nullptr};

} // namespace pl
