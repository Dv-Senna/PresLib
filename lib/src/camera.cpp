#include <iostream>

#include "instance.hpp"
#include "camera.hpp"



namespace pl
{
	Camera::Camera(pl::Instance &instance, const pl::Camera::CreateInfo &createInfos) : 
		m_instance {instance},
		m_position {createInfos.position},
		m_direction {createInfos.direction},
		m_velocity {createInfos.velocity},
		m_sensibility {createInfos.sensibility},
		m_verticalAngle {0.f},
		m_horizontalAngle {0.f},
		m_projection {1.f},
		m_view {1.f},
		m_transformation {1.f},
		m_projectionType {createInfos.projection},
		m_viewportSize {createInfos.viewportSize}
	{
		this->setProjection(m_projectionType);
	}
	


	void Camera::update(float dt)
	{
		if (m_instance.getEvent().isButtonDown(SDL_BUTTON_LEFT) || m_instance.getEvent().isButtonDown(SDL_BUTTON_RIGHT))
		{
			auto motion {m_instance.getEvent().getMouseMotion()};
			m_verticalAngle = Camera::s_normalizeAngles(
				m_verticalAngle - motion.y * m_sensibility * dt, -glm::pi<float> () / 2.f, glm::pi<float> () / 2.f
			);
			if (m_verticalAngle == glm::pi<float> () / 2.f)
				m_verticalAngle -= 0.00001f;
			else if (m_verticalAngle == -glm::pi<float> () / 2.f)
				m_verticalAngle += 0.00001f;

			m_horizontalAngle = Camera::s_normalizeAngles(m_horizontalAngle + motion.x * m_sensibility * dt);
			m_direction = {sinf(m_horizontalAngle), sinf(m_verticalAngle), -cosf(m_horizontalAngle)};
			m_direction = glm::normalize(m_direction);
		}

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_W))
			m_position += m_direction * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_S))
			m_position -= m_direction * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_D))
			m_position += glm::cross(m_direction, {0.f, 1.f, 0.f}) * m_velocity * dt;

		if (m_instance.getEvent().isKeyDown(SDL_SCANCODE_A))
			m_position -= glm::cross(m_direction, {0.f, 1.f, 0.f}) * m_velocity * dt;

		m_transformation = glm::lookAt(m_position, m_position + m_direction, {0.f, 1.f, 0.f});
	}
	


	const glm::mat4 &Camera::getTransformation() const noexcept
	{
		return m_transformation;
	}



	void Camera::setProjection(pl::graphics::Projection projection)
	{
		m_projectionType = projection;

		if (projection == pl::graphics::Projection::ortho)
			m_projection = glm::ortho(0.f, m_viewportSize.x, 0.f, m_viewportSize.y, 0.1f, (m_viewportSize.x + m_viewportSize.y) / 2.f);

		m_projection = glm::perspective(glm::radians(70.f), m_viewportSize.x / m_viewportSize.y, 0.1f, 100.f);
	}



	pl::graphics::Projection Camera::getProjection() const noexcept
	{
		return m_projectionType;
	}



	float Camera::s_normalizeAngles(float angle, float min, float max)
	{
		if (angle >= max)
		{
			angle -= (max - min);
			return s_normalizeAngles(angle, min, max);
		}

		if (angle < min)
		{
			angle += (max - min);
			return s_normalizeAngles(angle, min, max);
		}

		return angle;
	}
	


} // namespace pl
