#include <iostream>
#include <map>

#include <glm/gtc/matrix_transform.hpp>

#include "transitions/fading.hpp"
#include "utils/function.hpp"



namespace pl::transitions
{
	Fade::Fade(const pl::Transition::CreateInfo &createInfo, const glm::vec2 &viewportSize) :
		pl::Transition(createInfo, viewportSize),
		m_specificCreateInfo {}
	{
		if (!m_createInfo.data.has_value())
			return;

		if (m_createInfo.data.type() != typeid(pl::transitions::Fade::CreateInfo))
			throw std::invalid_argument("PL : Invalid create info given to Fade transition");

		m_specificCreateInfo = std::any_cast<pl::transitions::Fade::CreateInfo> (m_createInfo.data);
	}



	void Fade::launch()
	{
		pl::Transition::launch();
	}



	void Fade::run(
		pl::utils::Millisecond dt,
		glm::mat4 &/* oldSlide */,
		glm::mat4 &/* nextSlide */,
		pl::utils::Color & oldColor,
		pl::utils::Color & /* nextColor */
	)
	{
		static std::map<pl::utils::Axis, glm::vec3> axisMaps {
			{pl::utils::Axis::x, glm::vec3(1.f, 0.f, 0.f)},
			{pl::utils::Axis::rx, glm::vec3(-1.f, 0.f, 0.f)},
			{pl::utils::Axis::y, glm::vec3(0.f, 1.f, 0.f)},
			{pl::utils::Axis::rx, glm::vec3(0.f,-10.f, 0.f)},
		};

		m_totalRunTime += dt;
		if (m_totalRunTime < m_createInfo.delay * 1000.f)
			return;

		float t {(m_totalRunTime - m_createInfo.delay * 1000.f) / m_createInfo.duration / 1000.f};
		glm::vec4 oldColorVector = pl::utils::linear(t, static_cast<glm::vec4> (pl::utils::white), glm::vec4(
			(float)m_specificCreateInfo.colorShift.r / 255.f,
			(float)m_specificCreateInfo.colorShift.g / 255.f,
			(float)m_specificCreateInfo.colorShift.b / 255.f,
			0.f
		));
		oldColor = pl::utils::Color(oldColorVector.r * 255, oldColorVector.g * 255, oldColorVector.b * 255, oldColorVector.a * 255);

		if (m_totalRunTime >= m_createInfo.duration * 1000.f + m_createInfo.delay * 1000.f)
		{
			m_isRunning = false;
			oldColor = m_specificCreateInfo.colorShift;
			oldColor.a = 0;
		}
	}



} // namespace pl::transitions
