#include "pl/resourceManager.hpp"

#include "pl/assertation.hpp"



namespace pl {
	template <typename T>
	Resource<T>::Resource() :
		m_ptr {nullptr}
	{

	}


	template <typename T>
	Resource<T>::Resource(const pl::Resource<T> &resource) :
		m_ptr {resource.m_ptr}
	{

	}


	template <typename T>
	const pl::Resource<T> &Resource<T>::operator=(const pl::Resource<T> &resource) {
		m_ptr = resource.m_ptr;
		return *this;
	}


	template <typename T>
	bool Resource<T>::operator==(const pl::Resource<T> &resource) const noexcept {
		return m_ptr == resource.m_ptr;
	}


	template <typename T>
	T &Resource<T>::operator*() const noexcept {
		PL_ASSERT(m_ptr != nullptr, "Can't dereference null resource");
		return *m_ptr;
	}


	template <typename T>
	T *Resource<T>::operator->() const noexcept {
		PL_ASSERT(m_ptr != nullptr, "Can't dereference null resource");
		return m_ptr;
	}


	template <typename T>
	Resource<T>::Resource(T *ptr) :
		m_ptr {ptr}
	{

	}


} // namespace pl
