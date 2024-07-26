#include "pl/resourceManager.hpp"

#include "pl/instance.hpp"



namespace pl {
	template <>
	pl::Resource<pl::Image> ResourceManager::load<pl::Image, std::filesystem::path> (const std::filesystem::path &path) {
		for (auto &image : s_imageCounts) {
			if (image.first->getPath() != path)
				continue;

			pl::Resource<pl::Image> resource {image.first};
			++image.second;
			return resource;
		}

		pl::Resource<pl::Image> resource {s_memoryManager->allocate<pl::Image> (path)};
		s_imageCounts[resource.m_ptr] = 1;
		return resource;
	}


	template <>
	void ResourceManager::unload<pl::Image> (const pl::Resource<pl::Image> &resource) {
		auto it {s_imageCounts.find(resource.m_ptr)};
		PL_ASSERT(it != s_imageCounts.end(), "Can't unload image resource not loaded by the resource manager");
		--it->second;
		if (it->second != 0)
			return;

		s_memoryManager->free(resource.m_ptr);
		s_imageCounts.erase(it);
	}


	std::vector<pl::Resource<pl::Image>> ResourceManager::getImages() {
		std::vector<pl::Resource<pl::Image>> images {};
		images.reserve(s_imageCounts.size());
		for (const auto &image : s_imageCounts)
			images.push_back(pl::Resource<pl::Image> (image.first));
		return images;
	}


	pl::Count ResourceManager::getImageReferenceCount(const pl::Resource<pl::Image> &image) {
		auto it {s_imageCounts.find(image.m_ptr)};
		PL_ASSERT(it != s_imageCounts.end(), "Can't get reference count from image resource not loaded by the resource manager");
		return it->second;
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


	void ResourceManager::compile() {
		
	}


	pl::Instance *ResourceManager::s_instance {nullptr};
	pl::memory::HeapAllocator *ResourceManager::s_heapAllocator {nullptr};
	pl::memory::Manager *ResourceManager::s_memoryManager {nullptr};

	std::map<pl::Image*, pl::Count> ResourceManager::s_imageCounts {};

} // namespace pl
