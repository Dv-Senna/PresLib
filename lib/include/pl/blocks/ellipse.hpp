#pragma once

#include "../block.hpp"
#include "../utils/id.hpp"


namespace pl::blocks
{
	class Ellipse final :
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
				glm::vec2 position, size;
				pl::utils::Color color {pl::utils::undefined};
				pl::utils::Radians angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Ellipse(pl::Instance &instance, const pl::blocks::Ellipse::CreateInfo &createInfo);
			~Ellipse();

			void draw(const glm::mat4 &globalTransformation) override;

		private:
			static void s_load(pl::Instance &instance);
			static pl::utils::Id s_vertices, s_shaders[2], s_pipeline;
	};

} // namespace pl::blocks
