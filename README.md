# <img src="./logo.png" width="300px" alt="PresLib" />

<p align="center">
	<img src="https://img.shields.io/badge/version-0.1.0-informational" />
	<img src="https://img.shields.io/badge/Windows-success-success" />
	<img src="https://img.shields.io/badge/Linux-not tested-important" />
	<img src="https://img.shields.io/badge/MacOS M1-success-success" />
	<img src="https://img.shields.io/badge/automated-working on-ff0000" />
</p>

A C++ presentation library with LaTeX support (one day)


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
 - Run the exe
