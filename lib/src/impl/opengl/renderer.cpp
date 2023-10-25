#include <glad/glad.h>

#include "config.hpp"
#include "impl/opengl/renderer.hpp"



namespace pl::impl::opengl
{
	struct InternalState
	{
		SDL_GLContext context {nullptr};

		bool isComplete()
		{
			return context;
		}
	};
	
	class Deleter
	{
		public:
			void operator() (pl::impl::opengl::InternalState *internalState)
			{
				if (internalState == nullptr)
					return;

				if (internalState->context != nullptr)
					SDL_GL_DeleteContext(internalState->context);

				delete internalState;
			}
	};

	pl::impl::opengl::InternalState *checkInternalStateValidity(std::shared_ptr<void> opaqueState, const std::string &function)
	{
		if (opaqueState == nullptr)
			throw std::runtime_error("PL : OpenGL has no internal state in function " + function);
		pl::impl::opengl::InternalState *internalState {static_cast<pl::impl::opengl::InternalState*> (opaqueState.get())};
		if (!internalState->isComplete())
			throw std::runtime_error("PL : OpenGL is not complete in function " + function);
		return internalState;
	}
	
	#define checkInternalStateValidity(opaqueState) checkInternalStateValidity(opaqueState, __func__)

	void setOpenGLAttribute(SDL_GLattr attribute, int value, const std::string &attributeName)
	{
		if (SDL_GL_SetAttribute(attribute, value) != 0)
			throw std::runtime_error("PL : OpenGL can't set " + attributeName + " to " + std::to_string(value));
	}

	#define setOpenGLAttribute(attribute, value) setOpenGLAttribute(attribute, value, #attribute)



	void Renderer::setup(pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &/* createInfo */)
	{
		impl->internalState = std::shared_ptr<pl::impl::opengl::InternalState> (
			new pl::impl::opengl::InternalState(),
			pl::impl::opengl::Deleter()
		);
		pl::impl::opengl::InternalState *internalState {static_cast<pl::impl::opengl::InternalState*> (impl->internalState.get())};


		setOpenGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, pl::config::openglVersion.x);
		setOpenGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, pl::config::openglVersion.y);
		setOpenGLAttribute(SDL_GL_RED_SIZE, pl::config::openglBitsPerColor.r);
		setOpenGLAttribute(SDL_GL_GREEN_SIZE, pl::config::openglBitsPerColor.g);
		setOpenGLAttribute(SDL_GL_BLUE_SIZE, pl::config::openglBitsPerColor.b);
		setOpenGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		
		if (pl::config::useMSAA)
		{
			setOpenGLAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
			setOpenGLAttribute(SDL_GL_MULTISAMPLESAMPLES, pl::config::MSAASamplesCount);
		}


		internalState->context = SDL_GL_CreateContext(impl->window);
		if (internalState->context == nullptr)
			throw std::runtime_error("PL : OpenGL can't create the SDL3 context");

		
		if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
			throw std::runtime_error("PL : OpenGL can't load functions with glad : " + std::string(SDL_GetError()));
	}



	void Renderer::cleanup(pl::Renderer::Implementation *impl)
	{
		impl->internalState.reset();
	}



	void Renderer::cleanViewport(pl::Renderer::Implementation *impl, const pl::utils::Color &color)
	{
		(void)pl::impl::opengl::checkInternalStateValidity(impl->internalState);

		glClearColor((float)color.r / 255.f, (float)color.g / 255.f, (float)color.b / 255.f, (float)color.a / 255.f);
		glClear(GL_COLOR_BUFFER_BIT);
	}



	void Renderer::updateScreen(pl::Renderer::Implementation *impl)
	{
		(void)pl::impl::opengl::checkInternalStateValidity(impl->internalState);

		SDL_GL_SwapWindow(impl->window);
	}



} // namespace pl::impl::opengl
