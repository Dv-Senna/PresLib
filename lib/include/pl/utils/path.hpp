#pragma once

#include <string>

#include "pl/core.hpp"



namespace pl::utils {
	enum class PathState {
		eInvalid = 0,
		eDirectory,
		eFile
	};

	class PL_CORE Path final {
		public:
			Path();
			Path(const std::string &path);

			Path(const pl::utils::Path &path);
			const pl::utils::Path &operator=(const pl::utils::Path &path);

			inline const pl::utils::PathState &getState() const noexcept {return m_state;}
			inline const std::string &str() const noexcept {return m_path;}


		private:
			std::string m_path;
			pl::utils::PathState m_state;
	};

} // namespace pl::utils
