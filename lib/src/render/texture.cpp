#include "pl/render/texture.hpp"

#include <map>

#include <glad/gl.h>

#include "pl/assertation.hpp"



namespace pl::render {
	Texture::Texture(const pl::render::Texture::CreateInfos &createInfos) :
		m_texture {0},
		m_format {createInfos.format},
		m_size {createInfos.size},
		m_multisample {createInfos.multisample},
		m_mipmapLevelCount {createInfos.mipmapLevelCount}
	{
		PL_ASSERT(!m_multisample || (m_multisample && m_mipmapLevelCount == 1), "Multisample texture can't have mipmaps");

		static const std::map<pl::render::TextureFormat, GLenum> colorFormatMap {
			{pl::render::TextureFormat::eR8,           GL_R8},
			{pl::render::TextureFormat::eR32f,         GL_R32F},
			{pl::render::TextureFormat::eRG8,          GL_RG8},
			{pl::render::TextureFormat::eRG32f,        GL_RG32F},
			{pl::render::TextureFormat::eRGB8,         GL_RGB8},
			{pl::render::TextureFormat::eRGBA8,        GL_RGBA8},
			{pl::render::TextureFormat::eRGB32f,       GL_RGB32F},
			{pl::render::TextureFormat::eRGBA32f,      GL_RGBA32F},
			{pl::render::TextureFormat::eR11fG11fB10f, GL_R11F_G11F_B10F},
		};

		static const std::map<pl::render::TextureFormat, GLenum> colorFormatNoSizeMap {
			{pl::render::TextureFormat::eR8,           GL_RED},
			{pl::render::TextureFormat::eR32f,         GL_RED},
			{pl::render::TextureFormat::eRG8,          GL_RG},
			{pl::render::TextureFormat::eRG32f,        GL_RG},
			{pl::render::TextureFormat::eRGB8,         GL_RGB},
			{pl::render::TextureFormat::eRGBA8,        GL_RGBA},
			{pl::render::TextureFormat::eRGB32f,       GL_RGB},
			{pl::render::TextureFormat::eRGBA32f,      GL_RGBA},
			{pl::render::TextureFormat::eR11fG11fB10f, GL_RGB},
		};

		GLenum internalFormat {colorFormatMap.find(m_format)->second};


		glCreateTextures(m_multisample ? GL_TEXTURE_2D_MULTISAMPLE : GL_TEXTURE_2D, 1, &m_texture);
		if (m_multisample)
			glTextureStorage2DMultisample(m_texture, 4, internalFormat, m_size.x, m_size.y, GL_TRUE);

		else {
			glTextureStorage2D(m_texture, m_mipmapLevelCount, internalFormat, m_size.x, m_size.y);
			glTextureParameteri(m_texture, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTextureParameteri(m_texture, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);
		}

		if (createInfos.data != nullptr) {
			glTextureSubImage2D(
				m_texture, 0, 0, 0, m_size.x, m_size.y,
				colorFormatNoSizeMap.find(m_format)->second,
				GL_UNSIGNED_BYTE, createInfos.data
			);

			if (m_mipmapLevelCount != 1)
				glGenerateTextureMipmap(m_texture);
		}
	}


	Texture::~Texture() {
		if (m_texture != 0)
			glDeleteTextures(1, &m_texture);
	}


} // namespace pl::render
