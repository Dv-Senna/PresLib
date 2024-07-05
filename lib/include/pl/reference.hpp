#pragma once

#include <functional>



namespace pl {
	template <typename T>
	class Reference {
		T *ref;
		std::function<void(T*)> freeMethod;

		inline ~Reference() {
			if (freeMethod != nullptr)
				freeMethod(ref);
		}

		inline T *operator->() const noexcept {
			return ref;
		}

		inline operator T*() const noexcept {
			return ref;
		}
	};

} // namespace pl
