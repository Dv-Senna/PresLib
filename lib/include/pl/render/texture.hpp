#pragma once

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::render {
	enum class TextureFormat {
		eR8,
		eR32f,
		eRG8,
		eRG32f,
		eRGB8,
		eRGBA8,
		eRGB32f,
		eRGBA32f,
		eR11fG11fB10f,
	};

	class PL_CORE Texture final {
		public:
			struct CreateInfos {
				pl::Vec2i size;
				pl::render::TextureFormat format;
				bool multisample {false};
				pl::Count mipmapLevelCount {1};
				void *data {nullptr};
			};

			Texture(const pl::render::Texture::CreateInfos &createInfos);
			~Texture();

			inline const pl::Uint32 &getTexture() const noexcept {return m_texture;}
			inline const pl::Vec2i &getSize() const noexcept {return m_size;}


		private:
			pl::Uint32 m_texture;
			pl::render::TextureFormat m_format;
			pl::Vec2i m_size;
			bool m_multisample;
			pl::Count m_mipmapLevelCount;
	};

} // namespace pl::render
