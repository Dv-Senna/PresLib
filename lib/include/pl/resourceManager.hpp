#pragma once

#include "pl/core.hpp"
#include "pl/memory/heapAllocator.hpp"
#include "pl/memory/manager.hpp"
#include "pl/types.hpp"



namespace pl {
	struct Instance;
	struct ResourceManager;

	template <typename T>
	class PL_CORE Resource final {
		friend class ResourceManager;

		public:
			Resource();

			Resource(const pl::Resource<T> &resource);
			const pl::Resource<T> &operator=(const pl::Resource<T> &resource);

			T &operator*() const noexcept;
			T *operator->() const noexcept;

		protected:
			Resource(T *ptr);
			T *m_ptr;
	};



	class PL_CORE ResourceManager final {
		friend class pl::Instance;

		public:
			template <typename T, typename ...Args>
			static pl::Resource<T> load(const Args &...args);

			template <typename T>
			static void unload(const pl::Resource<T> &resource);


		protected:
			struct CreateInfos {
				pl::Instance *instance;
				pl::ByteCount heapSize;
			};

			static void create(const pl::ResourceManager::CreateInfos &createInfos);
			static void destroy();

		private:
			static pl::Instance *s_instance;
			static pl::memory::HeapAllocator *s_heapAllocator;
			static pl::memory::Manager *s_memoryManager;
	};

} // namespace pl


#include "pl/resourceManager.inl"