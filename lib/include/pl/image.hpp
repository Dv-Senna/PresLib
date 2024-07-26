#pragma once

#include <filesystem>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl {
	class PL_CORE Image final {
		public:
			Image(const std::filesystem::path &path);
			~Image();

			bool operator==(const pl::Image &image) const noexcept;

			inline const std::filesystem::path &getPath() const noexcept {return m_path;}

		private:
			std::filesystem::path m_path;
	};

} // namespace pl
