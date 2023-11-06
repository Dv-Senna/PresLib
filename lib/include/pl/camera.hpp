#pragma once

#include <glm/glm.hpp>


namespace pl
{
	struct Instance;

	class Camera
	{
		public:
			Camera(pl::Instance &instance);
			~Camera() = default;

			void update(float dt);
			const glm::vec4 &getTransformation() const noexcept;

		
		private:
			pl::Instance &m_instance;
			glm::vec3 m_position, m_direction;
			float m_velocity, m_sensibility;
	};

} // namespace pl
