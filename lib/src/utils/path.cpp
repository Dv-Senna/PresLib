#include "pl/utils/path.hpp"

#include <filesystem>



namespace pl::utils {
	Path::Path() :
		m_path {},
		m_state {pl::utils::PathState::eInvalid}
	{

	}


	Path::Path(const std::string &path) :
		m_path {path},
		m_state {pl::utils::PathState::eInvalid}
	{
		if (m_path == "")
			return;

		if (!std::filesystem::exists(m_path)) {
			m_path = "";
			return;
		}

		
	}


	Path::Path(const pl::utils::Path &path) :
		m_path {path.m_path},
		m_state {path.m_state}
	{

	}


	const pl::utils::Path &Path::operator=(const pl::utils::Path &path) {
		m_path = path.m_path;
		m_state = path.m_state;
		return *this;
	}


} // namespace pl::utils
