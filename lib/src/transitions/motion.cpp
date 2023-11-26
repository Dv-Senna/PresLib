#include <iostream>

#include <glm/gtc/matrix_transform.hpp>

#include "transitions/motion.hpp"
#include "utils/function.hpp"



namespace pl::transitions
{
	SlideTogether::SlideTogether(const pl::Transition::CreateInfo &createInfo) :
		pl::Transition(createInfo)
	{

	}



	void SlideTogether::launch()
	{
		pl::Transition::launch();
	}



	void SlideTogether::run(pl::utils::Millisecond dt, glm::mat4 &oldSlide, glm::mat4 &nextSlide)
	{
		m_totalRunTime += dt;
		if (m_totalRunTime < m_createInfo.delay * 1000.f)
			return;

		auto moveOldFar {glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 0.1f))};

		oldSlide = pl::utils::linear(
			(m_totalRunTime - m_createInfo.delay * 1000.f) / m_createInfo.duration / 1000.f,
			moveOldFar,
			glm::translate(moveOldFar, glm::vec3(2.f, 0.f, 0.f))
		);
		nextSlide = pl::utils::linear(
			(m_totalRunTime - m_createInfo.delay * 1000.f) / m_createInfo.duration / 1000.f,
			glm::translate(glm::mat4(1.f), glm::vec3(-2.f, 0.f, 0.f)),
			glm::mat4(1.f)
		);

		if (m_totalRunTime >= m_createInfo.duration * 1000.f)
		{
			m_isRunning = false;
			nextSlide = glm::mat4(1.f);
		}
	}



} // namespace pl::transitions
