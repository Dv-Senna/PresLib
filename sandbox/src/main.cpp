#define SDL_MAIN_HANDLED

#include <iostream>

#include "pl/preslib.hpp"
#include "pl/themes/modern.hpp"



int main(int argc, char *argv[])
{
	try
	{
		pl::Instance instance {};

		pl::themes::Modern theme {instance};
		theme.use();


		instance.getFonts().addFont("arial", "arial.ttf");
		instance.getFonts().addFont("title-font", "arial.ttf");

		std::cout << instance.getTitlePosition() << std::endl;



		pl::Slide slide {instance, pl::SlideFlag::no_background | pl::SlideFlag::no_overlay};
		instance.addSlide(&slide);

		pl::block::Line line {instance, {10, 20}, {30, 40}};
		slide.addChildren(&line);

		pl::block::Ellipse circle {instance, {100, 100}, 30};
		slide.addChildren(&circle);


		pl::Slide slide2 {instance};
		instance.addSlide(&slide2);

		pl::block::Ellipse ellipse {instance, {400, 400}, 20, 0.9f};
		ellipse.flipWidthAndHeight();
		slide2.addChildren(&ellipse);

		pl::block::Text text {instance, {500, 500}, "Hello World from PresLib !", "arial", 20};
		slide2.addChildren(&text);

		pl::block::Text text1 {instance, {500, 600}, "Hello Body from PresLib !", "arial", 50};
		slide2.addChildren(&text1);

		pl::block::Image image {instance, "image.png", {384, 583}, 2.0f};
		slide2.addChildren(&image);

		pl::block::Triangle triangle {
			instance,
			{pl::math::Vec2(100.0f, 100.0f), pl::math::Vec2(150.0f, 150.0f), pl::math::Vec2(150.0f, 100.0f)},
			pl::utils::colorUndefined,
			pl::DrawingType::outlined
		};
		slide2.addChildren(&triangle);



		pl::Slide themeSlide {instance};
		instance.addSlide(&themeSlide);
		themeSlide.setTitle("Un titre incroyable | modern");
	

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
	}

	return 0;
}