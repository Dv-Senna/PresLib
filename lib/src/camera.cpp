#include "instance.hpp"
#include "camera.hpp"



namespace pl
{
	Camera::Camera(pl::Instance &instance) : 
		m_instance {instance},
		m_position {0.f, 0.f, 0.f},
		m_direction {0.f, 0.f, 1.f}
	{

	}
	


	void Camera::update(float dt)
	{
		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_W))
			m_position += m_direction * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_S))
			m_position -= m_direction * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_D))
			m_position += glm::cross(m_direction, {0.f, 1.f, 0.f}) * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_A))
			m_position -= glm::cross(m_direction, {0.f, 1.f, 0.f}) * m_velocity * dt;

		if (m_instance.getEvent().isButtonDown(SDL_BUTTON_LEFT) || m_instance.getEvent().isButtonDown(SDL_BUTTON_RIGHT))
		{
			auto motion {m_instance.getEvent().getMouseMotion()};
		}
	}
	


	const glm::vec4 &Camera::getTransformation() const noexcept
	{

	}
	


} // namespace pl
