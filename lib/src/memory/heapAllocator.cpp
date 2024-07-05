#include "pl/memory/heapAllocator.hpp"

#include "pl/assertation.hpp"



namespace pl::memory {
	HeapAllocator::HeapAllocator(const pl::memory::HeapAllocator::CreateInfos &createInfos) :
		m_heap {nullptr},
		m_heapSize {createInfos.size},
		m_freeSpaces {}
	{
		m_heap = reinterpret_cast<pl::Byte*> (malloc(sizeof(pl::Byte) * m_heapSize));
		m_freeSpaces.push_back({m_heap, m_heapSize});
	}


	HeapAllocator::~HeapAllocator() {
		if (m_heap != nullptr)
			free(m_heap);
	}


	void *HeapAllocator::allocate(pl::ByteCount size, pl::ByteCount alignement) {
		PL_ASSERT(this->m_isValid(), "Can't allocate memory from an invalid heap allocator");
		PL_ASSERT(!m_freeSpaces.empty(), "Can't allocate memory from a full heap allocator");
		PL_ASSERT(size != 0, "Can't allocate 0 bytes");
		PL_ASSERT(alignement != 0, "Can't allocate with unknown alignement (for no restriction, use 1 instead of 0)");

		pl::ByteCount wantedSize {size + alignement};
		PL_ASSERT(wantedSize < 0xff, "Can't allocate more than 255 bytes of memory at once");

		for (auto freeSpace {m_freeSpaces.begin()}; freeSpace != m_freeSpaces.end(); ++freeSpace) {
			if (freeSpace->size < wantedSize)
				continue;

			pl::Byte *start {freeSpace->start};
			*start = wantedSize;
			pl::ByteCount offset {alignement - (reinterpret_cast<pl::ByteCount> (start) % alignement)};
			void *ptr {start + offset};

			for (pl::Byte *it {start + 1}; it != start + offset; ++it)
				*it = 0;
			for (pl::Byte *it {(pl::Byte*)ptr + size}; it != (pl::Byte*)ptr + size + alignement - offset; ++it)
				*it = 0;

			freeSpace->start += wantedSize;
			freeSpace->size -= wantedSize;
			// the minimal allocation size is 2 : 1 for `size` and 1 for `alignement`
			if (freeSpace->size < 2) {
				m_freeSpaces.erase(freeSpace);
			}

			return ptr;
		}

		return nullptr;
	}


	void HeapAllocator::free(void *ptr) noexcept {
		PL_ASSERT(this->m_isValid(), "Can't free memory from an invalid heap allocator");
		PL_ASSERT(ptr != nullptr, "Can't free `nullptr`");
		PL_ASSERT(ptr >= m_heap && ptr < m_heap + m_heapSize, "Can't free out-of-bound pointer");

		pl::Byte *start {reinterpret_cast<pl::Byte*> (ptr) - 1};
		while (*start == 0) --start;
		pl::ByteCount size {*start};

		pl::Count touchingSpaceCount {0};
		for (auto freeSpace {m_freeSpaces.begin()}; freeSpace != m_freeSpaces.end(); ++freeSpace) {
			if (touchingSpaceCount >= 2)
				return;

			if (start + size == freeSpace->start) {
				if (touchingSpaceCount == 1) {
					auto previous {std::prev(freeSpace)};
					previous->size += freeSpace->size;
					m_freeSpaces.erase(freeSpace);
					return;
				}

				freeSpace->start = start;
				freeSpace->size += size;
				return;
			}

			if (freeSpace->start + freeSpace->size == start) {
				freeSpace->size += size;
				++touchingSpaceCount;
				continue;
			}

			if (touchingSpaceCount == 1)
				++touchingSpaceCount;
		}

		for (auto freeSpace {m_freeSpaces.begin()}; freeSpace != m_freeSpaces.end(); ++freeSpace) {
			if (freeSpace->start < start)
				continue;
			m_freeSpaces.insert(freeSpace, {start, size});
			break;
		}
	}


	bool HeapAllocator::m_isValid() const noexcept {
		return m_heap != nullptr && m_heapSize != 0;
	}


} // namespace pl::memory
