#include <list>
#include <map>

#include <glad/glad.h>

#include "config.hpp"
#include "impl/opengl/renderer.hpp"
#include "object.hpp"
#include "utils/vertices.hpp"



namespace pl::impl::opengl
{
	class Vertices
	{
		public:
			Vertices(const pl::utils::VerticesFormat &format, const pl::utils::VerticesData &vertices) :
				m_vbo {0},
				m_vao {0},
				m_count {0}
			{
				static std::map<pl::utils::VerticesUsage, GLenum> verticesUsage {
					{pl::utils::VerticesUsage::streamDraw, GL_STREAM_DRAW},
					{pl::utils::VerticesUsage::staticDraw, GL_STATIC_DRAW},
					{pl::utils::VerticesUsage::dynamicDraw, GL_DYNAMIC_DRAW}
				};

				glCreateBuffers(1, &m_vbo);
				glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

					glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), verticesUsage[format.usage]);

					glGenVertexArrays(1, &m_vao);
					glBindVertexArray(m_vao);

						int stride {0};

						for (const auto &channel : format.channels)
						{
							if (!channel.second.enable)
								continue;

							stride += channel.second.dimension;
						}

						for (const auto &channel : format.channels)
						{
							if (!channel.second.enable)
								continue;

							glVertexAttribPointer(
								channel.second.location,
								channel.second.dimension,
								GL_FLOAT, GL_FALSE,
								stride * sizeof(float),
								reinterpret_cast<void*> (channel.second.start * sizeof(float))
							);
							glEnableVertexAttribArray(channel.second.location);
						}

					glBindVertexArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, 0);


				m_count = vertices.size() / stride;
			}



			~Vertices()
			{
				glDeleteVertexArrays(1, &m_vao);
				glDeleteBuffers(1, &m_vbo);
			}


			void draw()
			{
				glBindVertexArray(m_vao);
					glDrawArrays(GL_TRIANGLES, 0, m_count);
				glBindVertexArray(0);
			}
		

		private:
			GLuint m_vbo;
			GLuint m_vao;
			size_t m_count;
	};



	class Shader
	{
		public:
			Shader(const std::vector<unsigned char> &fileContent, const std::string &entryPoint);
			~Shader();

		private:
			GLuint m_shader;
			
	};



	struct InternalState
	{
		SDL_GLContext context {nullptr};
		std::list<pl::Object> objects {};


		bool isComplete()
		{
			return context;
		}

		~InternalState()
		{
			objects.erase(objects.begin(), objects.end());

			if (context != nullptr)
				SDL_GL_DeleteContext(context);
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
		impl->internalState = std::make_shared<pl::impl::opengl::InternalState> ();
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



	pl::utils::Id Renderer::registerObject(
		pl::Renderer::Implementation *impl,
		pl::utils::ObjectType type,
		const std::any &data,
		pl::utils::IdType idType
	)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		switch (type)
		{
			case pl::utils::ObjectType::vertices:
			{
				if (!data.has_value() || data.type() != typeid(pl::utils::Vertices))
					throw std::runtime_error("PL : OpenGL can't register object because data is not valid");

				const auto &vertices {std::any_cast<pl::utils::Vertices> (data)};
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Vertices> (vertices.format, vertices.data),
					pl::utils::generateNewID(idType),
					idType
				});

				break;
			}

			default:
				throw std::runtime_error("PL : OpenGL can't register object of the given type");
		}
	}



	pl::utils::ObjectType Renderer::getObjectType(pl::Renderer::Implementation *impl, pl::utils::Id objectID)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		for (const auto &object : internalState->objects)
		{
			if (object.id == objectID)
				return object.type;
		}

		return pl::utils::ObjectType::invalid;
	}



} // namespace pl::impl::opengl
