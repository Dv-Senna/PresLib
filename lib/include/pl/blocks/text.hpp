#pragma once

#include <string>
#include <vector>

#include "../block.hpp"
#include "../utils/id.hpp"


namespace pl::blocks
{
	class Text final :
		public pl::Block,
		public pl::BlockWithPosition,
		public pl::BlockWithOrientation,
		public pl::BlockWithColor,
		public pl::BlockWithDistortion
	{
		public:
			struct CreateInfo
			{
				std::string text;
				int fontSize;
				std::string font;
				glm::vec2 position;
				pl::utils::Color color {pl::utils::undefined};
				pl::utils::Radians angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Text(pl::Instance &instance, const pl::blocks::Text::CreateInfo &CreateInfo);
			~Text();

			void draw(const glm::mat4 &globalTransformation) override;

		protected:
			static void s_load(pl::Instance &instance);
			static pl::utils::Id s_shaders[2], s_pipeline;

			std::vector<pl::utils::Id> m_vertices, m_textures;
	};

} // namespace pl::blocks
