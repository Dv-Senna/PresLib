#pragma once

#include "../block.hpp"
#include "../utils/id.hpp"


namespace pl::blocks
{
	class Line : 
		public pl::Block,
		public pl::BlockWithPosition,
		public pl::BlockWithSize,
		public pl::BlockWithOrientation,
		public pl::BlockWithColor,
		public pl::BlockWithDistortion
	{
		public:
			struct CreateInfo
			{
				glm::vec2 position;
				float length;
				float thickness;
				pl::utils::Color color {pl::utils::undefined};
				float angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Line(pl::Instance &instance, const pl::blocks::Line::CreateInfo &createInfo);
			~Line();

			void draw(const glm::mat4 &globalTransformation) override;
	};

} // namespace pl::blocks
