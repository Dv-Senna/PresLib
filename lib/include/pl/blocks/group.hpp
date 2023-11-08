#pragma once

#include <list>
#include <memory>

#include "../block.hpp"


namespace pl::blocks
{
	class Group final : 
		public pl::Block,
		public pl::BlockWithPosition,
		public pl::BlockWithSize,
		public pl::BlockWithOrientation,
		public pl::BlockWithDistortion
	{
		public:
			struct CreateInfo
			{
				glm::vec2 position {0.f, 0.f};
				glm::vec2 scale {1.f, 1.f};
				float angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Group(pl::Instance &instance, const pl::blocks::Group::CreateInfo &createInfo);
			~Group();

			void draw(const glm::mat4 &globalTransformation) override;
			void registerBlock(std::shared_ptr<pl::Block> block) override;


		private:
			std::list<std::shared_ptr<pl::Block>> m_blocks;
	};

} // namespace pl::blocks
