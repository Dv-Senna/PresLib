#include "../defines.inl"
#include "modern.hpp"



namespace pl::themes
{
	template <pl::GraphicsApi API>
	Modern<API>::Modern(pl::Instance<API> &instance) : 
		pl::Theme (),
		m_background {},
		m_backgroundTriangles {},
		m_titleRectangles {}
	{
		m_background = std::make_unique<pl::blocks::Group<API>> (instance);
		this->style.background = (*m_background).getImplementation();

		this->style.mainColor = {0, 100, 255};
		this->style.secondColor = {70, 70, 70};
		this->style.thirdColor = {255, 255, 255};

		instance.getFonts().add("roboto", "roboto/Roboto-Black.ttf");
		
		this->style.textColor = {0, 0, 0};
		this->style.titleColor = {255, 255, 255};
		this->style.objectColor = {49, 145, 255};
		this->style.backgroundColor = {200, 200, 200};


		m_backgroundTriangles[0] = std::make_unique<pl::blocks::Triangle<API, pl::args::Color>> (
			instance,
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.635416666667f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.675925925925925f
			),
			pl::args::color = this->style.mainColor
		);
		this->style.background->addChild((*m_backgroundTriangles[0]).getImplementation());

		m_backgroundTriangles[1] = std::make_unique<pl::blocks::Triangle<API, pl::args::Color>> (
			instance,
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.6875f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.72222222222222f
			),
			pl::args::color = this->style.thirdColor
		);
		this->style.background->addChild((*m_backgroundTriangles[1]).getImplementation());

		m_backgroundTriangles[2] = std::make_unique<pl::blocks::Triangle<API, pl::args::Color>> (
			instance,
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.791666666666667f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT)
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.814814814814814814f
			),
			pl::args::color = this->style.secondColor
		);
		this->style.background->addChild((*m_backgroundTriangles[2]).getImplementation());


		m_titleRectangles[0] = std::make_unique<pl::blocks::Rectangle<API, pl::args::Color>> (
			instance,
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.375f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.02777777777778f
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.0925925925925925f
			),
			pl::args::color = this->style.mainColor
		);
		this->style.background->addChild((*m_titleRectangles[0]).getImplementation());

		m_titleRectangles[1] = std::make_unique<pl::blocks::Rectangle<API, pl::args::Color>> (
			instance,
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.390625f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.00925925925925925f
			),
			pl::math::Vec2f(
				static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH), static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.0925925925925925f
			),
			pl::args::color = this->style.secondColor
		);
		this->style.background->addChild((*m_titleRectangles[1]).getImplementation());

		this->style.titlePosition = {static_cast<float> (PL_DEFAULT_VIEWPORT_WIDTH) * 0.40104166666666667f, static_cast<float> (PL_DEFAULT_VIEWPORT_HEIGHT) * 0.02777777777778f};
		this->style.titleSize = 50;
		this->style.titleFont = "roboto";


		instance.setTheme(*this);
	}

	

	template <pl::GraphicsApi API>
	Modern<API>::~Modern()
	{

	}

	


} // namespace pl::themes