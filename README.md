# <img src="./logo.png" width="300px" alt="PresLib" />

<p align="center">
	<img src="https://img.shields.io/badge/version-0.5.0-informational" />
	<img src="https://img.shields.io/badge/Windows-success-success" />
	<img src="https://img.shields.io/badge/Linux-not tested-important" />
	<img src="https://img.shields.io/badge/MacOS-not tested-important" />
	<img src="https://img.shields.io/badge/automated-working on-ff0000" />
</p>

A C++ presentation library with LaTeX support.

## Features
 - Draw primitives (circle, rectangle, triangle, line, ellipse) filled and outlined
 - Render text with custom font
 - Handle LaTeX equation (make use of pdflatex and convert of ImageMagick)
 - Handle creation of custom themes (color, font, title position, background, ...)


## Installation

### Windows MinGW
 - Download the repo : 
 	```ps
	git clone https://github.com/Dv-Senna/PresLib.git
	```
 - Download and compiled (or get directly binaries) [SDL3](https://github.com/libsdl-org/SDL), [freetype2](http://freetype.org/), [glad](https://glad.dav1d.de/), [glm](https://github.com/g-truc/glm), [stb_image](https://github.com/nothings/stb) and [utf8-cpp](https://github.com/nemtrif/utfcpp)
	- Put each one into vendors/{name_of_the_dep}
	- Put headers in an include/{name_of_deps} folder
	- Put libraries in a lib folder
	- If there is a dll, copy it into sandbox/bin or next to your own executable
 - Compile with
	```ps
	premake5 gmake2
	make all
	```
 - Run `.\sandbox\bin\sandbox.exe`


## Usage

You can use directly the project to code your own presentation. Just open `sandbox/src/main.cpp` and start typing new code.

> **Warning**  
It's recommended to encased the code in a `try`-`catch` block. Know that each error will throw an `std::runtime_error(...)`. 

To use the library, start by creating a `pl::Instance`. Most function in PresLib take their paramaters as a `pl::Foo::CreateInfo` structure (like Vulkan). This allow you to name your arguments and to pass only the arguments you want (except for the mandatory ones). Register a new slide to the instance and register a block (here a rectangle) to the slide. Don't forget to run the instance. You're done !

```cpp

#include <exception>
#include <iostream>
#include <pl/preslib.hpp>

int main(int, char *[])
{
	try
	{
		pl::Instance::CreateInfo instanceCreateInfo {};
		instanceCreateInfo.viewportSize = {1920, 1080};
		instanceCreateInfo.graphicsApi = pl::graphics::Api::OpenGL;
		pl::Instance instance {instanceCreateInfo};

		auto slide = instance.registerSlide();
		auto rectangle = instance.registerBlock(slide, {pl::Block::Type::rectangle, pl::blocks::Rectangle::CreateInfo(
			{800, 200},
			{600, 300},
			pl::utils::red
		)});

		instance.run();
	}

	catch (const std::exception &exception)
	{
		std::cerr << "ERROR : " << exception.what() << std::endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

```