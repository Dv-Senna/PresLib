#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

#include "utils/loadImage.hpp"



class PixelDeleter
{
	public:
		void operator() (unsigned char *pixels)
		{
			stbi_image_free(pixels);
			pixels = nullptr;
		}
};


namespace pl::utils
{
	pl::utils::Id loadImage(pl::Instance &instance, const std::string &path, glm::vec2 &size)
	{
		int channelCount {};
		int width {}, height {};
		stbi_set_flip_vertically_on_load(true);
		std::shared_ptr<unsigned char> pixels {
			stbi_load(path.c_str(), &width, &height, &channelCount, 0),
			PixelDeleter()
		};
		if (pixels == nullptr)
			throw std::runtime_error("PL : Could not load image " + path);

		size.x = width;
		size.y = height;

		pl::graphics::Texture textureInfos {
			size,
			pixels,
			channelCount == 4 ? pl::graphics::ColorFormat::r8g8b8a8 : pl::graphics::ColorFormat::r8g8b8
		};
		return instance.getRenderer().registerObject(
			pl::utils::ObjectType::texture,
			textureInfos
		);
	}
	
} // namespace pl::utils
