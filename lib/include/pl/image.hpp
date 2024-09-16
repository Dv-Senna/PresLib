#pragma once

#include <filesystem>

#include "pl/core.hpp"
#include "pl/render/texture.hpp"
#include "pl/types.hpp"



namespace pl {
	struct Instance;

	class PL_CORE Image final {
		public:
			Image(const std::filesystem::path &path);
			~Image();

			bool operator==(const pl::Image &image) const noexcept;

			void compile(pl::Instance *instance);

			inline const std::filesystem::path &getPath() const noexcept {return m_path;}
			inline const pl::render::Texture &getTexture() const noexcept {return *m_texture;}

		private:
			std::filesystem::path m_path;
			pl::render::Texture *m_texture;
			pl::Instance *m_instance;
	};

} // namespace pl
