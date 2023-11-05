#include "transformation.hpp"



namespace pl::utils
{
	glm::mat4 rotate2D(pl::utils::Radians angle)
	{
		return glm::mat4(
			cosf(angle), -sinf(angle), 0.f, 0.f,
			sinf(angle), cosf(angle), 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f	
		);
	}



	glm::mat4 translate(const glm::vec2 &offset)
	{
		return glm::mat4(
			1.f, 0.f, 0.f, offset.x,
			0.f, 1.f, 0.f, offset.y,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}



	glm::mat4 scale(const glm::vec2 &scale)
	{
		return glm::mat4(
			scale.x, 0.f, 0.f, 0.f,
			0.f, scale.y, 0.f, 0.f,
			0.f, 0.f, 1.f, 0.f,
			0.f, 0.f, 0.f, 1.f
		);
	}



} // namespace pl::utils
