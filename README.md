# <img src="./logo.png" width="300px" alt="PresLib" />

<p align="center">
	<img src="https://img.shields.io/badge/version-0.3.0-informational" />
	<img src="https://img.shields.io/badge/Windows-success-success" />
	<img src="https://img.shields.io/badge/Linux-not tested-important" />
	<img src="https://img.shields.io/badge/MacOS M1-success-success" />
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
 - Download and compiled (or get directly binaries) [SDL2](https://github.com/libsdl-org/SDL), [SDL2_ttf](https://github.com/libsdl-org/SDL_ttf), [SDL2_image](https://github.com/libsdl-org/SDL_image), [SDL2_latex](https://github.com/Dv-Senna/SDL_latex) and [SDL2_gfx](https://github.com/ferzkopp/SDL_gfx)
	- Put each one into vendors/{name_of_the_dep}
	- Put headers in an include/SDL2 folder
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

To use the library, start by creating a `pl::Instance<...>`. As a template argument, use the graphics api of your choice. For the moment, only `pl::GraphicsApi::SDL2_renderer` is supported. Then you can create a slide with `pl::Slide slide {instance}`. The order of creation is the order of slides. From here you can create a block of your choice and add it to the slide. The first added block will be the farthest and the last the nearest. Finally you have to run the instance. Here is an example :

```cpp

#include <exception>
#include <iostream>
#include <pl/preslib.hpp>

int main(int, char *[])
{
	try
	{
		pl::Instance<pl::GraphicsApi::SDL2_renderer> instance {};
		pl::Slide slide {instance};

		pl::blocks::Rectangle rectangle {instance, {100, 100}, {600, 300}, pl::utils::green, pl::RenderMethod::border};
		slide.add(&rectangle);

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