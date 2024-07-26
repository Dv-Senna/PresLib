#include "pl/image.hpp"

#include <map>

#include <stb_image.h>

#include "pl/instance.hpp"
#include "pl/config.hpp"



namespace pl {
	Image::Image(const std::filesystem::path &path) :
		m_path {pl::Config::getImageFolderPath() / path},
		m_texture {nullptr},
		m_instance {nullptr}
	{

	}


	Image::~Image() {
		if (m_instance == nullptr)
			return;
		if (m_texture != nullptr)
			m_instance->freeObject(m_texture);
	}


	bool Image::operator==(const pl::Image &image) const noexcept {
		return m_path == image.m_path;
	}


	void Image::compile(pl::Instance *instance) {
		static const std::map<pl::Int, pl::render::TextureFormat> channelsCountMap {
			{1, pl::render::TextureFormat::eR8},
			{2, pl::render::TextureFormat::eRG8},
			{3, pl::render::TextureFormat::eRGB8},
			{4, pl::render::TextureFormat::eRGBA8}
		};

		m_instance = instance;

		pl::Vec2i size {};
		pl::Int channelsCount {};
		void *data {stbi_load(m_path.c_str(), &size.x, &size.y, &channelsCount, 0)};

		pl::render::Texture::CreateInfos textureCreateInfos {};
		textureCreateInfos.data = data;
		textureCreateInfos.format = channelsCountMap.find(channelsCount)->second;
		textureCreateInfos.size = size;
		textureCreateInfos.mipmapLevelCount = 5;
		textureCreateInfos.multisample = 1;
		m_texture = m_instance->allocateObject<pl::render::Texture> (textureCreateInfos);

		stbi_image_free(data);
	}


} // namespace pl
