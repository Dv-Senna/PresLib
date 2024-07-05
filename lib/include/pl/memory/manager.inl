#include "pl/memory/manager.hpp"

#include "pl/assertation.hpp"



namespace pl::memory {
	template <typename T, typename ...Args>
	T *Manager::allocate(Args ...args) {
		PL_ASSERT(m_allocator != nullptr, "Can't allocate memory from a non-defined allocator");

		T *buffer {reinterpret_cast<T*> (m_allocator->allocate(sizeof(T), alignas(T)))};
		T *ptr {new(buffer) T(args...)};
		return ptr;
	}


	template <typename T>
	void Manager::free(T *ptr) {
		PL_ASSERT(m_allocator != nullptr, "Can't free memory from a non-defined allocator");

		ptr->~T();
		m_allocator->free(ptr);
	}


	void Manager::setAllocator(pl::memory::Allocator *allocator) noexcept {
		m_allocator = allocator;
	}


	pl::memory::Allocator *Manager::setAllocator() const noexcept {
		return m_allocator;
	}


} // namespace pl::memory
