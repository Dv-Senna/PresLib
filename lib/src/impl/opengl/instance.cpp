#include <iostream>
#include <stdexcept>

#include <SDL3/SDL.h>
#include <glad/glad.h>

#include "impl/opengl/instance.hpp"


namespace pl::opengl
{
	struct InternalState
	{
		SDL_Window *window;
		SDL_GLContext context;
	};


	void cleanInternalState(pl::opengl::InternalState *internalState)
	{
		if (internalState == nullptr)
			return;

		if (internalState->context != nullptr)
			SDL_GL_DeleteContext(internalState->context);

		if (internalState->window != nullptr)
			SDL_DestroyWindow(internalState->window);
	}


	class Deleter
	{
		public:
			void operator() (void *data)
			{
				if (data == nullptr)
					return;

				auto internalState {static_cast<pl::opengl::InternalState*> (data)};
				cleanInternalState(internalState);
				delete internalState;
			}
	};



	void Instance::setup(pl::InstanceImplementation *impl, const pl::InstanceCreateInfo &createInfo)
	{
		std::cout << "Create an opengl window : " << createInfo.viewportSize << std::endl;

		SDL_Window *window {SDL_CreateWindow(
			createInfo.presentationTitle.c_str(),
			createInfo.viewportSize.x, createInfo.viewportSize.y,
			uint32_t(SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN)
		)};
		if (window == nullptr)
			throw std::runtime_error("PL : Can't create a window : " + std::string(SDL_GetError()));


		std::cout << "Set context attributes" << std::endl;

		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
		SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);

		std::cout << "Create context" << std::endl;

		SDL_GLContext context {SDL_GL_CreateContext(window)};
		if (context == nullptr)
			throw std::runtime_error("PL : Can't create the SDL_GL context : " + std::string(SDL_GetError()));

		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
			throw std::runtime_error("PL : Can't load OpenGL function with SDL_GL_GetProcAddress : " + std::string(SDL_GetError()));

		
		impl->internalState = std::shared_ptr<pl::opengl::InternalState> (
			new pl::opengl::InternalState(),
			Deleter()
		);
		auto internalState {static_cast<pl::opengl::InternalState*> (impl->internalState.get())};
		internalState->window = window;
		internalState->context = context;

		int width {}, height {};
		SDL_GetWindowSize(window, &width, &height);

		glViewport(0, (createInfo.viewportSize.y - height), width, createInfo.viewportSize.y);
	}



	void Instance::cleanup(pl::InstanceImplementation *impl)
	{
		auto internalState {static_cast<pl::opengl::InternalState*> (impl->internalState.get())};
		if (internalState == nullptr)
			return;

		cleanInternalState(internalState);
	}



	void Instance::run(pl::InstanceImplementation *impl)
	{
		auto internalState {static_cast<pl::opengl::InternalState*> (impl->internalState.get())};
		if (internalState == nullptr || internalState->window == nullptr || internalState->context == nullptr)
			throw std::runtime_error("PL : You try to use an instance implementation that is not valid");


		SDL_Event event {};

		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_EVENT_KEY_DOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return;

				if (event.type == SDL_EVENT_QUIT)
					return;
			}


			glClearColor(0.5, 0, 0, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			SDL_GL_SwapWindow(internalState->window);
		}
	}



} // namespace pl::opengl
