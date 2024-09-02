#include <iostream>
#include <exception>

#include <glad/gl.h>

#include <pl/preslib.hpp>
#include <pl/config.hpp>

#include <pl/blocks/image.hpp>
#include <pl/blocks/triangle.hpp>
#include <pl/memory/heapAllocator.hpp>
#include <pl/render/vertexLayout.hpp>
#include <pl/render/pipeline.hpp>
#include <pl/resourceManager.hpp>



int main(int, char *[]) {
	try {
		pl::Instance::CreateInfos instanceCreateInfos {};
		instanceCreateInfos.presentationName = "Example";
		instanceCreateInfos.viewportSize = {16*70, 9*70};
		instanceCreateInfos.objectHeapSize = 1024*1024;
		pl::Instance instance {instanceCreateInfos};


		pl::Slide::CreateInfos slideCreateInfos {};
		slideCreateInfos.viewportSize = {-1, -1};
		pl::Slide slide1 {slideCreateInfos};
		pl::Slide slide2 {slideCreateInfos};

		instance.registerSlide("slide1", &slide1);
		instance.registerSlide("slide2", &slide2);

		pl::blocks::Triangle::CreateInfos triangleCreateInfos {};
		triangleCreateInfos.color = {1.f, 0.f, 0.f};
		triangleCreateInfos.position = {0.f, 0.f};
		triangleCreateInfos.vertices = {
			pl::Vec2f(0.f, 200.f),
			pl::Vec2f(200.f, -200.f),
			pl::Vec2f(-200.f, -200.f)
		};
		pl::blocks::Triangle triangle {triangleCreateInfos};
		slide1.registerBlock(&triangle);

		triangleCreateInfos.color = {0.f, 1.f, 0.f};
		triangleCreateInfos.position = {0.f, 0.f};
		triangleCreateInfos.vertices = {
			pl::Vec2f(200.f, 200.f),
			pl::Vec2f(400.f, -200.f),
			pl::Vec2f(-200.f, -200.f)
		};
		pl::blocks::Triangle triangle2 {triangleCreateInfos};
		//slide1.registerBlock(&triangle2);

		pl::blocks::Image::CreateInfos imageCreateInfos {};
		imageCreateInfos.path = "logo.png";
		imageCreateInfos.position = {300.f, 0.f};
		imageCreateInfos.scale = {.2f, .2f};
		pl::blocks::Image image {imageCreateInfos};
		image.setRotation({0.f, -1.f, 0.f});
		slide1.registerBlock(&image);

		imageCreateInfos.path = "spritesheet.png";
		imageCreateInfos.position = {0.f, 0.f};
		imageCreateInfos.scale = {.5f, .5f};
		pl::blocks::Image image2 {imageCreateInfos};
		slide2.registerBlock(&image2);

		std::cout << "Loaded images : " << pl::ResourceManager::getImages().size() << std::endl;

		pl::Config::setCustomRenderCallback([&] () {
			image.rotate(3.14159f * 2.f / 60.f);
		});

		slide1.registerBlock(&triangle2);

		instance.mainloop();
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
