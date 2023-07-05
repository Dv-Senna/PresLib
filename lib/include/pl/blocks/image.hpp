#pragma once

#include <iostream>

#include "../block.hpp"
#include "../impl/SDL2_renderer/blocks/image.hpp"
#include "../math/vector.hpp"


namespace pl::blocks
{
	/// @brief A block to load and draw images
	/// @tparam API The graphics api used
	template <pl::GraphicsApi API>
	class Image final : public pl::Block<API>
	{
		public:
			/// @brief A block to load and draw images
			/// @param instance The current instance of PresLib
			/// @param path The path of the image relative to `PL_DEFAULT_IMAGE_FOLDER_PATH`
			/// @param pos The position of the image in px
			/// @param scale A scale factor to apply to the image
			Image(
				pl::Instance<API> &instance,
				const std::string &path,
				const pl::math::Vec2f &pos,
				float scale = 1.0f
			) : pl::Block<API> ()
			{
				if constexpr (API == pl::GraphicsApi::SDL2_renderer)
					this->m_impl = new pl::impl::SDL2_renderer::blocks::Image(instance.getImplementation(), path, pos, scale);

				
				if (this->m_impl == nullptr)
					throw std::runtime_error("PL : image's implementation's creation failed");
			}
	};

} // namespace pl::blocks
