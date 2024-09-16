# <img src="./logo.png" width="300px" alt="PresLib" />

<p align="center">
	<img src="https://img.shields.io/badge/version-dev0.6.0-informational" />
	<img src="https://img.shields.io/badge/Windows-success-error" />
	<img src="https://img.shields.io/badge/Linux-success-error" />
	<img src="https://img.shields.io/badge/MacOS-not tested-important" />
</p>

A C++ presentation library with LaTeX support.

## Features
 - [ ] Draw primitives (circle, rectangle, triangle, line, ellipse) filled and outlined
 - [ ] Render text with custom font
 - [ ] Handle LaTeX equation (make use of pdflatex and convert of ImageMagick)
 - [ ] Handle creation of custom themes (color, font, title position, background, ...)


## Installation

 - To build PresLib, you need [SDL2](https://github.com/libsdl-org/SDL/tree/SDL2), the [Vulkan SDK](https://www.lunarg.com/vulkan-sdk/) and [CMake](https://cmake.org/download/) installed on your system

 - Download the repo and its submodules : 
 	```bash
	git clone --recurse-submodules https://github.com/Dv-Senna/PresLib.git
	```
 - Create a build folder :
	```bash
	mkdir build
	cd build
	```
 - Configure with
	```bash
	cmake ..
	```
 - Use your tools (makefile, visual studio solution, etc) to build the project
 - Run `build/sandbox/PresLib_sandbox` from the root of the repo


## Usage

You can use directly the project to code your own presentation. Just open `sandbox/src/main.cpp` and start typing new code.

> **Warning**  
It's recommended to encased the code in a `try`-`catch` block. Know that each error will throw an exception derivated from `std::exception`. 

To use the library, start by creating a `pl::Instance`. Most function in PresLib take their paramaters as a `pl::Foo::CreateInfo` structure. This allow you to name your arguments and to pass only the arguments you want (except for the mandatory ones). Register a new slide to the instance and register a block (here a rectangle) to the slide. Don't forget to run the instance. You're done !

```cpp

#include <exception>
#include <iostream>
#include <pl/preslib.hpp>

int main(int, char *[]) {
	try {
		pl::Instance::CreateInfos instanceCreateInfos {};
		instanceCreateInfos.presentationName = "Example";
		instanceCreateInfos.viewportSize = {16*70, 9*70};
		pl::Instance instance {instanceCreateInfos};


		pl::Slide::CreateInfos slideCreateInfos {};
		slideCreateInfos.viewportSize = {-1, -1};
		pl::Slide slide {slideCreateInfos};

		instance.registerSlide("slide", &slide);

		pl::blocks::Triangle::CreateInfos triangleCreateInfos {};
		triangleCreateInfos.color = {1.f, 0.f, 0.f};
		triangleCreateInfos.position = {0.f, 0.f, 0.f};
		triangleCreateInfos.vertices = {
			pl::Vec3f(0.f, 0.5f, 0.f),
			pl::Vec3f(0.5f, -0.5f, 0.f),
			pl::Vec3f(-0.5f, -0.5f, 0.f)
		};
		pl::blocks::Triangle triangle {triangleCreateInfos};
		slide.registerBlock(&triangle);

		instance.mainloop();
	}

	catch (const std::exception &exception) {
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

```
