#include <glm/gtc/matrix_transform.hpp>

#include "blocks/group.hpp"



namespace pl::blocks
{
	Group::Group(pl::Instance &instance, const pl::blocks::Group::CreateInfo &createInfo) : 
		pl::Block(instance),
		pl::BlockWithPosition(createInfo.position),
		pl::BlockWithSize(createInfo.scale),
		pl::BlockWithOrientation(createInfo.angle, createInfo.rotationCenter),
		pl::BlockWithDistortion(createInfo.distortion),
		m_blocks {}
	{

	}
	


	Group::~Group()
	{

	}
	


	void Group::draw(const glm::mat4 &globalTransformation)
	{
		glm::vec3 rotationCenter {m_rotationCenter.x * m_size.x, m_rotationCenter.y * m_size.y, 0.f};
		glm::mat4 transform {1.f};

		transform = glm::translate(transform, {m_position.x, m_position.y, 0.f});
		transform = glm::translate(transform, rotationCenter);
		transform = glm::rotate(transform, static_cast<float> (m_angle), {0.f, 0.f, 1.f});
		transform = glm::translate(transform, -rotationCenter);
		transform = glm::scale(transform, {m_size.x, m_size.y, 1.f});
		transform = globalTransformation * transform * m_distortion;

		for (auto &block : m_blocks)
		{
			block->draw(transform);
		}
	}
	


	void Group::registerBlock(std::shared_ptr<pl::Block> block)
	{
		m_blocks.push_back(block);
	}
	


} // namespace pl::blocks
