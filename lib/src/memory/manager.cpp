#include "pl/memory/manager.hpp"

#include "pl/assertation.hpp"



namespace pl::memory {
	Manager::Manager(const pl::memory::Manager::CreateInfos &createInfos) :
		m_allocator {createInfos.allocator},
		m_allocationCount {0}
	{

	}


	Manager::~Manager() {
		PL_ASSERT(m_allocationCount != 0, "You have leaked some memory (" + std::to_string(m_allocationCount) + " allocations)");
	}


} // namespace pl::memory
