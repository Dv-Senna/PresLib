#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "graphics/projection.hpp"


namespace pl
{
	struct Instance;

	class Camera
	{
		public:
			struct CreateInfo
			{
				glm::vec2 viewportSize;
				glm::vec3 position {0.f, 0.f, 1.f};
				glm::vec3 direction {0.f, 0.f, -1.f};
				float velocity {1.f};
				float sensibility {0.01f};
				pl::graphics::Projection projection {pl::graphics::Projection::ortho};
			};

			Camera(pl::Instance &instance, const pl::Camera::CreateInfo &createInfos);
			~Camera() = default;

			void update(float dt);
			const glm::mat4 &getTransformation() const noexcept;
			void setProjection(pl::graphics::Projection projection);
			pl::graphics::Projection getProjection() const noexcept;

		
		private:
			static float s_normalizeAngles(float angle, float min = 0.f, float max = 2 * glm::pi<float> ());

			pl::Instance &m_instance;
			glm::vec3 m_position, m_direction;
			float m_velocity, m_sensibility;
			float m_verticalAngle, m_horizontalAngle;
			glm::mat4 m_projection, m_view, m_transformation;
			pl::graphics::Projection m_projectionType;
			glm::vec2 m_viewportSize;
	};

} // namespace pl
