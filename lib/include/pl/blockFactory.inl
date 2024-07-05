#include "pl/blockFactory.hpp"



namespace pl {
	template <typename T>
	PL_REQUIRES(pl::concepts::IsBlock<T>)
	pl::Reference<T> BlockFactory::create(const typename T::CreateInfos &createInfos) {
		pl::Reference<T> ref {};
		ref.ref = m_memoryManager.allocate<T> (createInfos);
		ref.freeMethod = [this] (T *ptr) {
			this->m_memoryManager.free<T> (ptr);
		};

		return ref;
	}

} // namespace pl
