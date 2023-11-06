#include "block.hpp"



namespace pl
{
	Block::Block(pl::Instance &instance) :
		m_instance {instance}
	{

	}



	BlockWithPosition::BlockWithPosition(const glm::vec2 &position) : m_position {position}
	{

	}



	void BlockWithPosition::setPosition(const glm::vec2 &position)
	{
		m_position = position;
	}



	const glm::vec2 &BlockWithPosition::getPosition() const noexcept
	{
		return m_position;
	}



	BlockWithOrientation::BlockWithOrientation(pl::utils::Radians angle, const glm::vec2 &orientationCenter) :
		m_angle {angle},
		m_rotationCenter {orientationCenter}
	{

	}



	void BlockWithOrientation::setOrientation(pl::utils::Radians angle)
	{
		m_angle = angle;
	}



	pl::utils::Radians BlockWithOrientation::getOrientation() const noexcept
	{
		return m_angle;
	}



	void BlockWithOrientation::setRotationCenter(const glm::vec2 &rotationCenter)
	{
		m_rotationCenter = rotationCenter;
	}



	const glm::vec2 &BlockWithOrientation::getRotationCenter() const noexcept
	{
		return m_rotationCenter;
	}



	BlockWithSize::BlockWithSize(const glm::vec2 &size) : m_size {size}
	{

	}




	void BlockWithSize::setSize(const glm::vec2 &size)
	{
		m_size = size;
	}



	const glm::vec2 &BlockWithSize::getSize() const noexcept
	{
		return m_size;
	}



	BlockWithColor::BlockWithColor(const pl::utils::Color &color) : m_color {color}
	{

	}



	void BlockWithColor::setColor(const pl::utils::Color &color)
	{
		m_color = color;
	}



	const pl::utils::Color &BlockWithColor::getColor() const noexcept
	{
		return m_color;
	}



	BlockWithDistortion::BlockWithDistortion(const glm::mat4 &distortion) : m_distortion {distortion}
	{
		
	}



	void BlockWithDistortion::setDistortion(const glm::mat4 &distortion)
	{
		m_distortion = distortion;
	}



	const glm::mat4 &BlockWithDistortion::getDistortion() const noexcept
	{
		return m_distortion;
	}



} // namespace pl
