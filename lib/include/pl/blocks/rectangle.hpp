#pragma once

#include <glm/glm.hpp>

#include "../block.hpp"
#include "../utils/id.hpp"
#include "line.hpp"


namespace pl::blocks
{
	class Rectangle final :
		public pl::Block,
		public pl::BlockWithPosition,
		public pl::BlockWithSize,
		public pl::BlockWithOrientation,
		public pl::BlockWithColor,
		public pl::BlockWithDistortion
	{
		friend class pl::blocks::Line;

		public:
			struct CreateInfo
			{
				glm::vec2 position, size;
				pl::utils::Color color {pl::utils::undefined};
				pl::utils::Radians angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Rectangle(pl::Instance &instance, const pl::blocks::Rectangle::CreateInfo &createInfo);
			~Rectangle();

			void draw(const glm::mat4 &globalTransformation) override;

		protected:
			static void s_load(pl::Instance &instance);
			static pl::utils::Id s_vertices, s_shaders[2], s_pipeline;
	};


} // namespace pl::blocks
