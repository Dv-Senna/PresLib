#include "themes/modern.hpp"



namespace pl::themes
{
	Modern::Modern(pl::Instance &instance) : 
		pl::Theme(instance),
		m_backgroundTriangles {},
		m_titleRectangles {}
	{
		m_background = std::make_unique<pl::block::Group> (m_instance);

		m_instance.getColors().addColor("main-color", {0, 100, 255});
		m_instance.getColors().addColor("second-color", {70, 70, 70});
		m_instance.getColors().addColor("third-color", {255, 255, 255});
		
		m_scheme = {
			.text = {0, 0, 0},
			.title = {255, 255, 255},
			.object = {49, 145, 255},
			.background = {200, 200, 200},
		};


		m_backgroundTriangles[0] = std::make_unique<pl::block::Triangle> (
			m_instance,
			std::array<pl::math::Vec2, 3> ({pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH - 700, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT - 350
			)}),
			m_instance.getColors().getColor("main-color")
		);
		m_background->addChildren(m_backgroundTriangles[0].get());

		m_backgroundTriangles[1] = std::make_unique<pl::block::Triangle> (
			m_instance,
			std::array<pl::math::Vec2, 3> ({pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH - 600, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT - 300
			)}),
			m_instance.getColors().getColor("third-color")
		);
		m_background->addChildren(m_backgroundTriangles[1].get());

		m_backgroundTriangles[2] = std::make_unique<pl::block::Triangle> (
			m_instance,
			std::array<pl::math::Vec2, 3> ({pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH - 400, PL_DEFAULT_VIEWPORT_HEIGHT
			), pl::math::Vec2(
				PL_DEFAULT_VIEWPORT_WIDTH, PL_DEFAULT_VIEWPORT_HEIGHT - 200
			)}),
			m_instance.getColors().getColor("second-color")
		);
		m_background->addChildren(m_backgroundTriangles[2].get());


		m_titleRectangles[0] = std::make_unique<pl::block::Rectangle> (
			instance, pl::math::Rect(
				PL_DEFAULT_VIEWPORT_WIDTH - 1200, 30,
				PL_DEFAULT_VIEWPORT_WIDTH, 100
			),
			m_instance.getColors().getColor("main-color")
		);
		m_background->addChildren(m_titleRectangles[0].get());

		m_titleRectangles[1] = std::make_unique<pl::block::Rectangle> (
			instance, pl::math::Rect(
				PL_DEFAULT_VIEWPORT_WIDTH - 1170, 10,
				PL_DEFAULT_VIEWPORT_WIDTH, 100
			),
			m_instance.getColors().getColor("second-color")
		);
		m_background->addChildren(m_titleRectangles[1].get());

		m_titlePosition = {PL_DEFAULT_VIEWPORT_WIDTH - 1150, 20};
		m_titleFontSize = 30;
	}

	

	Modern::~Modern()
	{

	}

	


} // namespace pl::themes