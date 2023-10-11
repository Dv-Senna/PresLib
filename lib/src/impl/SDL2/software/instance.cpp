#include <stdexcept>

#include "impl/SDL2/software/instance.hpp"



namespace pl::SDL2::software
{
	void cleanInternalState(pl::SDL2::software::Instance::InternalState *internalState)
	{
		if (internalState == nullptr)
			return;

		if (internalState->renderer != nullptr)
			SDL_DestroyRenderer(internalState->renderer);

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

				auto internalState {static_cast<pl::SDL2::software::Instance::InternalState*> (data)};
				cleanInternalState(internalState);
				delete internalState;
			}
	};



	void Instance::setup(pl::InstanceImplementation *impl, const pl::InstanceCreateInfo &createInfo)
	{
		SDL_Window *window {SDL_CreateWindow(
			createInfo.presentationTitle.c_str(),
			SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
			createInfo.viewportSize.x, createInfo.viewportSize.y,
			SDL_WINDOW_SHOWN | SDL_WINDOW_FULLSCREEN_DESKTOP
		)};
		if (window == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 window : " + std::string(SDL_GetError()));

		SDL_Renderer *renderer {SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE)};
		if (renderer == nullptr)
			throw std::runtime_error("PL : Can't create an SDL2 software renderer : " + std::string(SDL_GetError()));

		
		impl->internalState = std::shared_ptr<pl::SDL2::software::Instance::InternalState> (
			new pl::SDL2::software::Instance::InternalState(),
			Deleter()
		);
		auto internalState {static_cast<pl::SDL2::software::Instance::InternalState*> (impl->internalState.get())};
		internalState->window = window;
		internalState->renderer = renderer;
	}



	void Instance::cleanup(pl::InstanceImplementation *impl)
	{
		auto internalState {static_cast<pl::SDL2::software::Instance::InternalState*> (impl->internalState.get())};
		if (internalState == nullptr)
			return;

		cleanInternalState(internalState);
	}



	void Instance::run(pl::InstanceImplementation *impl)
	{
		auto internalState {static_cast<pl::SDL2::software::Instance::InternalState*> (impl->internalState.get())};
		if (internalState == nullptr || internalState->window == nullptr || internalState->renderer == nullptr)
			throw std::runtime_error("PL : You try to use an instance implementation that is not valid");


		SDL_Event event {};

		while (true)
		{
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					return;

				if (event.type == SDL_QUIT)
					return;
			}


			SDL_SetRenderDrawColor(internalState->renderer, 0, 0, 0, 255);
			SDL_RenderClear(internalState->renderer);

			SDL_RenderPresent(internalState->renderer);
		}
	}



} // namespace pl::SDL2::software
