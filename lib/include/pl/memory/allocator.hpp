#pragma once

#include "pl/types.hpp"


namespace pl::memory {
	class Allocator {
		public:
			Allocator() = default;
			virtual ~Allocator() = default;

			virtual void *allocate(pl::ByteCount size, pl::ByteCount alignement) = 0;
			virtual void free(void *ptr) noexcept = 0;
	};

} // namespace pl::memory
