#include <fstream>
#include <iostream>
#include <list>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "config.hpp"
#include "graphics/framebuffer.hpp"
#include "graphics/pipeline.hpp"
#include "graphics/texture.hpp"
#include "graphics/uniform.hpp"
#include "graphics/vertices.hpp"
#include "impl/opengl/renderer.hpp"
#include "object.hpp"
#include "utils/file.hpp"



namespace pl::impl::opengl
{
	class Vertices
	{
		public:
			Vertices(const pl::graphics::VerticesFormat &format, const pl::graphics::VerticesData &vertices) :
				m_vbo {0},
				m_vao {0},
				m_count {0}
			{
				static std::map<pl::graphics::VerticesUsage, GLenum> verticesUsage {
					{pl::graphics::VerticesUsage::streamDraw, GL_STREAM_DRAW},
					{pl::graphics::VerticesUsage::staticDraw, GL_STATIC_DRAW},
					{pl::graphics::VerticesUsage::dynamicDraw, GL_DYNAMIC_DRAW}
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
			Shader(const std::vector<unsigned char> &fileContent, const std::string &entryPoint, pl::graphics::ShaderType type) : 
				m_shader {0},
				m_type {type}
			{
				static std::map<pl::graphics::ShaderType, GLenum> types {
					{pl::graphics::ShaderType::vertex, GL_VERTEX_SHADER},
					{pl::graphics::ShaderType::fragment, GL_FRAGMENT_SHADER},
					{pl::graphics::ShaderType::geometry, GL_GEOMETRY_SHADER},
				};

				m_shader = glCreateShader(types[m_type]);
				glShaderBinary(
					1, &m_shader, GL_SHADER_BINARY_FORMAT_SPIR_V, fileContent.data(), fileContent.size() * sizeof(unsigned char)
				);
				glSpecializeShader(m_shader, entryPoint.c_str(), 0, nullptr, nullptr);

				GLint success {};
				glGetShaderiv(m_shader, GL_COMPILE_STATUS, &success);
				if (success == GL_FALSE)
					throw std::runtime_error("PL : OpenGL Failed to specialized shader");
			}

			~Shader()
			{
				glDeleteShader(m_shader);
			}

			inline GLuint getInternalObject() const noexcept
			{
				return m_shader;
			}


		private:
			GLuint m_shader;
			pl::graphics::ShaderType m_type;
	};



	class UniformsBuffer
	{
		public:
			struct FieldInfos
			{
				std::string name;
				pl::graphics::UniformFieldType type;
				size_t offset;
			};


		private:
			std::vector<pl::impl::opengl::UniformsBuffer::FieldInfos>::iterator m_getFieldInfoByName(const std::string &name)
			{
				for (auto info {m_fieldsInfos.begin()}; info != m_fieldsInfos.end(); ++info)
				{
					if (info->name == name)
						return info;
				}

				return m_fieldsInfos.end();
			}


			static void m_fillBufferWithData(std::vector<unsigned char> &buffer, size_t offset, size_t size, const void *data)
			{
				if (offset > buffer.size())
					throw std::runtime_error("PL : OpenGL can't fill buffer because the offset is not valid : " + std::to_string(offset));

				for (size_t i {0}; i < size; ++i)
					buffer[offset + i] = *reinterpret_cast<unsigned char*> (reinterpret_cast<size_t> (data) + i);
			}


			struct FieldAlignement
			{
				size_t alignement;
				size_t size;
			};


		public:
			UniformsBuffer(
				GLuint /* program */, const pl::graphics::UniformsFormat &formats, const std::string & /* name */, int bindingPoint
			) : 
				m_ubo {0},
				m_fieldsInfos {},
				m_bufferSize {0},
				m_bindingPoint {bindingPoint}
			{
				static std::map<pl::graphics::UniformFieldType, pl::impl::opengl::UniformsBuffer::FieldAlignement> fieldAlignments {
					{pl::graphics::UniformFieldType::floating, {4, 4}},
					{pl::graphics::UniformFieldType::integer, {4, 4}},
					{pl::graphics::UniformFieldType::vec2, {8, 8}},
					{pl::graphics::UniformFieldType::vec3, {16, 12}},
					{pl::graphics::UniformFieldType::vec4, {16, 16}},
					{pl::graphics::UniformFieldType::mat4, {16, 64}},
				};

				size_t offset {0};

				for (size_t i {0}; i < formats.size(); ++i)
				{
					auto alignments = fieldAlignments[formats[i].type];

					if (offset % alignments.alignement != 0)
						offset += alignments.alignement - (offset % alignments.alignement);

					m_fieldsInfos.push_back({
						formats[i].name,
						formats[i].type,
						offset
					});

					offset += alignments.size;
				}

				m_bufferSize = offset;

				glCreateBuffers(1, &m_ubo);
				glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

					glBufferData(GL_UNIFORM_BUFFER, m_bufferSize, nullptr, GL_DYNAMIC_DRAW);

				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}


			~UniformsBuffer()
			{
				glDeleteBuffers(1, &m_ubo);
			}


			void bind()
			{
				glBindBufferBase(GL_UNIFORM_BUFFER, m_bindingPoint, m_ubo);
			}


			void setValues(const std::vector<pl::graphics::UniformFieldValue> &values)
			{				
				std::vector<unsigned char> buffer {};
				buffer.resize(m_bufferSize);

				glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);

					void *ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_READ_ONLY);
					memcpy(buffer.data(), ptr, buffer.size());
					glUnmapBuffer(GL_UNIFORM_BUFFER);


					for (const auto &value : values)
					{
						auto info {this->m_getFieldInfoByName(value.name)};
						if (info == m_fieldsInfos.end())
							throw std::runtime_error("PL : OpenGL can't set value of uniform '" + value.name + "' because it doesn't exist");

						std::shared_ptr<void> data {nullptr};

						switch (info->type)
						{
							case pl::graphics::UniformFieldType::floating:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									4,
									std::make_shared<float> (std::any_cast<float> (value.value)).get()
								);
								break;

							case pl::graphics::UniformFieldType::integer:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									4,
									std::make_shared<int> (std::any_cast<int> (value.value)).get()
								);
								break;

							case pl::graphics::UniformFieldType::vec2:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									8,
									glm::value_ptr(std::any_cast<glm::vec2> (value.value))
								);
								break;

							case pl::graphics::UniformFieldType::vec3:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									12,
									glm::value_ptr(std::any_cast<glm::vec3> (value.value))
								);
								break;

							case pl::graphics::UniformFieldType::vec4:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									16,
									glm::value_ptr(std::any_cast<glm::vec4> (value.value))
								);
								break;

							case pl::graphics::UniformFieldType::mat4:
								pl::impl::opengl::UniformsBuffer::m_fillBufferWithData(
									buffer,
									info->offset,
									64,
									glm::value_ptr(std::any_cast<glm::mat4> (value.value))
								);
								break;
						}
					}


					ptr = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
					memcpy(ptr, buffer.data(), buffer.size());
					glUnmapBuffer(GL_UNIFORM_BUFFER);

				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}


		private:
			GLuint m_ubo;
			std::vector<pl::impl::opengl::UniformsBuffer::FieldInfos> m_fieldsInfos;
			size_t m_bufferSize;
			int m_bindingPoint;
	};



	class Pipeline
	{
		public:
			Pipeline(const std::vector<pl::impl::opengl::Shader*> &shaders, const std::vector<pl::graphics::Uniform> &uniforms) : 
				m_program {},
				m_ubos {}
			{
				m_program = glCreateProgram();

				for (const auto &shader : shaders)
					glAttachShader(m_program, shader->getInternalObject());
				
				glLinkProgram(m_program);

				GLint success {};
				glGetProgramiv(m_program, GL_LINK_STATUS, &success);
				if (success == GL_FALSE)
					throw std::runtime_error("PL : OpenGL can't link program");


				for (const auto &uniform : uniforms)
				{
					m_ubos[uniform.name] = std::make_shared<pl::impl::opengl::UniformsBuffer> (
						m_program, uniform.formats, uniform.name, uniform.bindingPoint
					);
				}
			}


			~Pipeline()
			{
				m_ubos.clear();
				glDeleteProgram(m_program);
			}


			void use()
			{
				glUseProgram(m_program);

				for (auto &ubo : m_ubos)
					ubo.second->bind();
			}

			void unuse()
			{
				glUseProgram(0);
			}


			pl::impl::opengl::UniformsBuffer *getUbo(const std::string &name)
			{
				return m_ubos[name].get();
			}


			inline GLuint getProgram() const noexcept
			{
				return m_program;
			}


		private:
			GLuint m_program;
			std::map<std::string, std::shared_ptr<pl::impl::opengl::UniformsBuffer>> m_ubos;
	};



	class Texture
	{
		struct FormatValues
		{
			size_t size;
			GLenum internalFormat;
			GLenum format;
		};

		public:
			Texture(const pl::graphics::Texture &infos) : 
				m_texture {0},
				m_size {infos.size},
				m_target {GL_TEXTURE_2D}
			{
				static std::map<pl::graphics::ColorFormat, pl::impl::opengl::Texture::FormatValues> formats {
					{pl::graphics::ColorFormat::r8g8b8, {24, GL_RGB8, GL_RGB}},
					{pl::graphics::ColorFormat::r8g8b8a8, {32, GL_RGBA8, GL_RGBA}},
					{pl::graphics::ColorFormat::r8, {8, GL_R8, GL_RED}}
				};
				static std::map<pl::graphics::Filter, GLenum> minFilters {
					{pl::graphics::Filter::nearest, GL_NEAREST_MIPMAP_LINEAR},
					{pl::graphics::Filter::linear, GL_LINEAR_MIPMAP_LINEAR}
				};
				static std::map<pl::graphics::Filter, GLenum> magFilters {
					{pl::graphics::Filter::nearest, GL_NEAREST},
					{pl::graphics::Filter::linear, GL_LINEAR}
				};

				glGenTextures(1, &m_texture);

				if (infos.multisample == 0)
				{
					if (infos.format == pl::graphics::ColorFormat::r8)
						glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

					glBindTexture(GL_TEXTURE_2D, m_texture);
						glTexImage2D(
							GL_TEXTURE_2D,
							0, formats[infos.format].internalFormat,
							m_size.x, m_size.y,
							0, formats[infos.format].format, GL_UNSIGNED_BYTE, infos.pixels.get()
						);
						glGenerateMipmap(GL_TEXTURE_2D);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilters[infos.minFilter]);
						glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilters[infos.magFilter]);

					glBindTexture(GL_TEXTURE_2D, 0);

					if (infos.format == pl::graphics::ColorFormat::r8)
						glPixelStorei(GL_UNPACK_ALIGNMENT, 0);
				}

				else
				{
					glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, m_texture);
						glTexImage2DMultisample(
							GL_TEXTURE_2D_MULTISAMPLE,
							infos.multisample,
							formats[infos.format].format,
							m_size.x, m_size.y, GL_TRUE
						);

					glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);

					m_target = GL_TEXTURE_2D_MULTISAMPLE;
				}
			}


			void bind(int bindingPoint)
			{
				glActiveTexture(GL_TEXTURE0 + bindingPoint);
				glBindTexture(m_target, m_texture);
			}


			void unbind()
			{
				glBindTexture(m_target, 0);
			}


			~Texture()
			{
				glDeleteTextures(1, &m_texture);
			}


			inline GLuint getObject() const noexcept
			{
				return m_texture;
			}


		private:
			GLuint m_texture;
			glm::vec2 m_size;
			GLenum m_target;
	};



	class Framebuffer
	{
		public:
			Framebuffer(const pl::graphics::Framebuffer &infos, const pl::impl::opengl::Texture &texture, pl::utils::Id textureID) :
				m_framebuffer {0},
				m_renderbuffer {0},
				m_textureID {textureID}
			{
				static std::map<pl::graphics::DepthStencilFormat, GLenum> renderBufferFormats {
					{pl::graphics::DepthStencilFormat::depth24stencil8, GL_DEPTH24_STENCIL8}
				};

				glGenFramebuffers(1, &m_framebuffer);
				glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);

					if (infos.depthStencilFormat != pl::graphics::DepthStencilFormat::none)
					{
						glGenRenderbuffers(1, &m_renderbuffer);
						glBindRenderbuffer(GL_RENDERBUFFER, m_renderbuffer);

							if (infos.multisample == 0)
							{
								glRenderbufferStorage(
									GL_RENDERBUFFER, renderBufferFormats[infos.depthStencilFormat], infos.size.x, infos.size.y
								);
							}

							else
							{
								glRenderbufferStorageMultisample(
									GL_RENDERBUFFER, infos.multisample,
									renderBufferFormats[infos.depthStencilFormat], infos.size.x, infos.size.y
								);
							}

							glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_renderbuffer);

						glBindRenderbuffer(GL_RENDERBUFFER, 0);
					}

					GLenum textureTarget {GL_TEXTURE_2D};
					if (infos.multisample != 0)
						textureTarget = GL_TEXTURE_2D_MULTISAMPLE;

					glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, textureTarget, texture.getObject(), 0);

					if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
						throw std::runtime_error("PL : OpenGL can't make attachement to the framebuffer");

				glBindFramebuffer(GL_FRAMEBUFFER, 0);
			}

			~Framebuffer()
			{
				if (m_renderbuffer != 0)
					glDeleteRenderbuffers(1, &m_renderbuffer);

				glDeleteFramebuffers(1, &m_framebuffer);
			}

			inline pl::utils::Id getTextureID() const noexcept
			{
				return m_textureID;
			}

			inline GLuint getObject() const noexcept
			{
				return m_framebuffer;
			}

			void use()
			{
				glBindFramebuffer(GL_FRAMEBUFFER, m_framebuffer);
			}

		
		private:
			GLuint m_framebuffer, m_renderbuffer;
			pl::utils::Id m_textureID;
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


	std::shared_ptr<void> getObject(const std::list<pl::Object> &objects, pl::utils::Id id, pl::utils::ObjectType type)
	{
		for (const auto &object : objects)
		{
			if (object.id != id)
				continue;

			if (object.type != type)
				throw std::runtime_error("PL : OpenGL object is not of the right type");

			return object.data;
		}

		throw std::runtime_error("PL : OpenGL can't find object with id " + std::to_string(id));
	}

	void APIENTRY debugOutput(
		GLenum source,
		GLenum type,
		unsigned int id,
		GLenum severity,
		GLsizei /* length */,
		const char *message,
		const void * /* userParam */
	)
	{
		static std::ofstream output {"debug.opengl.log"};

		if (id == 131169 || id == 131185 || id == 131218 || id == 131204)
			return;

		output << "---------------" << std::endl;
		output << "Debug message (" << id << "): " <<  message << std::endl;

		switch (source)
		{
			case GL_DEBUG_SOURCE_API:             output << "Source: API"; break;
			case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   output << "Source: Window System"; break;
			case GL_DEBUG_SOURCE_SHADER_COMPILER: output << "Source: Shader Compiler"; break;
			case GL_DEBUG_SOURCE_THIRD_PARTY:     output << "Source: Third Party"; break;
			case GL_DEBUG_SOURCE_APPLICATION:     output << "Source: Application"; break;
			case GL_DEBUG_SOURCE_OTHER:           output << "Source: Other"; break;
		} output << std::endl;

		switch (type)
		{
			case GL_DEBUG_TYPE_ERROR:               output << "Type: Error"; break;
			case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: output << "Type: Deprecated Behaviour"; break;
			case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  output << "Type: Undefined Behaviour"; break; 
			case GL_DEBUG_TYPE_PORTABILITY:         output << "Type: Portability"; break;
			case GL_DEBUG_TYPE_PERFORMANCE:         output << "Type: Performance"; break;
			case GL_DEBUG_TYPE_MARKER:              output << "Type: Marker"; break;
			case GL_DEBUG_TYPE_PUSH_GROUP:          output << "Type: Push Group"; break;
			case GL_DEBUG_TYPE_POP_GROUP:           output << "Type: Pop Group"; break;
			case GL_DEBUG_TYPE_OTHER:               output << "Type: Other"; break;
		} output << std::endl;
		
		switch (severity)
		{
			case GL_DEBUG_SEVERITY_HIGH:         output << "Severity: high"; break;
			case GL_DEBUG_SEVERITY_MEDIUM:       output << "Severity: medium"; break;
			case GL_DEBUG_SEVERITY_LOW:          output << "Severity: low"; break;
			case GL_DEBUG_SEVERITY_NOTIFICATION: output << "Severity: notification"; break;
		} output << std::endl;
		output << std::endl;
	}



	void Renderer::setup(pl::Renderer::Implementation *impl, const pl::Renderer::CreateInfo &/*createInfo*/)
	{
		impl->internalState = std::make_shared<pl::impl::opengl::InternalState> ();
		pl::impl::opengl::InternalState *internalState {static_cast<pl::impl::opengl::InternalState*> (impl->internalState.get())};


		setOpenGLAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, pl::config::openglVersion.x);
		setOpenGLAttribute(SDL_GL_CONTEXT_MINOR_VERSION, pl::config::openglVersion.y);
		setOpenGLAttribute(SDL_GL_RED_SIZE, pl::config::openglBitsPerColor.r);
		setOpenGLAttribute(SDL_GL_GREEN_SIZE, pl::config::openglBitsPerColor.g);
		setOpenGLAttribute(SDL_GL_BLUE_SIZE, pl::config::openglBitsPerColor.b);
		setOpenGLAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

		#ifndef __NDEBUG__
			setOpenGLAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
		#endif
		
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

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		glFrontFace(GL_CW);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_FRONT);


		#ifndef __NDEBUG__

			glEnable(GL_DEBUG_OUTPUT);
			glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
			glDebugMessageCallback(pl::impl::opengl::debugOutput, nullptr);
			glDebugMessageControl(GL_DONT_CARE/*GL_DEBUG_SOURCE_API*/, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);

		#endif
	}



	void Renderer::cleanup(pl::Renderer::Implementation *impl)
	{
		impl->internalState.reset();
	}



	void Renderer::cleanViewport(pl::Renderer::Implementation *impl, const pl::utils::Color &color, pl::graphics::CleanFlag flag)
	{
		static std::map<pl::graphics::CleanFlag, GLbitfield> cleanFlagMap {
			{pl::graphics::CleanFlag::color, GL_COLOR_BUFFER_BIT},
			{pl::graphics::CleanFlag::depth, GL_DEPTH_BUFFER_BIT},
			{pl::graphics::CleanFlag::stencil, GL_STENCIL_BUFFER_BIT}
		};

		(void)pl::impl::opengl::checkInternalStateValidity(impl->internalState);

		GLbitfield cleanFlags {0};

		for (size_t i {0}; i < (size_t)pl::graphics::CleanFlag::__last; ++i)
		{
			if (((size_t)flag & (1 << i)) != 0)
				cleanFlags |= cleanFlagMap[static_cast<pl::graphics::CleanFlag> (1 << i)];
		}

		if (((size_t)flag & (size_t)pl::graphics::CleanFlag::color) != 0)
			glClearColor((float)color.r / 255.f, (float)color.g / 255.f, (float)color.b / 255.f, (float)color.a / 255.f);

		glClear(cleanFlags);
	}



	void Renderer::updateScreen(pl::Renderer::Implementation *impl)
	{
		(void)pl::impl::opengl::checkInternalStateValidity(impl->internalState);

		SDL_GL_SwapWindow(impl->window);
	}



	pl::utils::Id Renderer::registerObject(
		pl::Renderer::Implementation *impl,
		pl::utils::ObjectType type,
		const std::any &data
	)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};
		pl::utils::Id id {0};

		switch (type)
		{
			case pl::utils::ObjectType::vertices:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Vertices))
					throw std::runtime_error("PL : OpenGL can't register vertices because data is not valid");

				const auto &vertices {std::any_cast<pl::graphics::Vertices> (data)};
				id = pl::utils::generateNewID();
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Vertices> (vertices.format, vertices.data),
					id
				});

				break;
			}

			case pl::utils::ObjectType::shader:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Shader))
					throw std::runtime_error("PL : OpenGL can't register shader because data is not valid");

				const auto &shader {std::any_cast<pl::graphics::Shader> (data)};
				std::vector<unsigned char> fileContent {pl::utils::getBinaryFileContent(shader.file)};
				id = pl::utils::generateNewID();
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Shader> (fileContent, shader.entryPoint, shader.type),
					id
				});

				break;
			}

			case pl::utils::ObjectType::pipeline:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Pipeline))
					throw std::runtime_error("PL : OpenGL can't register pipeline because data is not valid");

				const auto &pipeline {std::any_cast<pl::graphics::Pipeline> (data)};
				std::vector<pl::impl::opengl::Shader*> shaders {};
				shaders.reserve(pipeline.shaders.size());

				for (const auto &shader : pipeline.shaders)
				{
					shaders.push_back(static_cast<pl::impl::opengl::Shader*> (pl::impl::opengl::getObject(
						internalState->objects, shader, pl::utils::ObjectType::shader
					).get()));
				}
				
				id = pl::utils::generateNewID();
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Pipeline> (shaders, pipeline.uniforms),
					id
				});

				break;
			}

			case pl::utils::ObjectType::texture:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Texture))
					throw std::runtime_error("PL : OpenGL can't register texture because data is not valid");

				const auto &texture {std::any_cast<pl::graphics::Texture> (data)};
				id = pl::utils::generateNewID();
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Texture> (texture),
					id
				});

				break;
			}

			case pl::utils::ObjectType::framebuffer:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Framebuffer))
					throw std::runtime_error("PL : OpenGL can't register framebuffer because data is not valid");


				const auto &framebuffer {std::any_cast<pl::graphics::Framebuffer> (data)};

				pl::graphics::Texture textureInfos {
					framebuffer.size,
					nullptr,
					framebuffer.colorFormat,
					framebuffer.minFilter,
					framebuffer.magFilter,
					framebuffer.multisample
				};
				auto textureID {pl::impl::opengl::Renderer::registerObject(impl, pl::utils::ObjectType::texture, textureInfos)};
				auto texture {static_cast<pl::impl::opengl::Texture*> (pl::impl::opengl::getObject(
					internalState->objects, textureID, pl::utils::ObjectType::texture
				).get())};
				
				id = pl::utils::generateNewID();
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Framebuffer> (framebuffer, *texture, textureID),
					id
				});

				break;
			}

			default:
				throw std::runtime_error("PL : OpenGL can't register object of the given type");
		}

		return id;
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



	void Renderer::usePipeline(pl::Renderer::Implementation *impl, pl::utils::Id pipeline)
	{
		if (pipeline == 0)
		{
			glUseProgram(0);
			return;
		}

		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto pipelineObject {static_cast<pl::impl::opengl::Pipeline*> (pl::impl::opengl::getObject(
			internalState->objects, pipeline, pl::utils::ObjectType::pipeline
		).get())};
		pipelineObject->use();
	}



	void Renderer::drawVertices(pl::Renderer::Implementation *impl, pl::utils::Id vertices, bool forceNormalRenderMode)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto verticesObject {static_cast<pl::impl::opengl::Vertices*> (pl::impl::opengl::getObject(
			internalState->objects, vertices, pl::utils::ObjectType::vertices
		).get())};

		if (forceNormalRenderMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		verticesObject->draw();

		if (forceNormalRenderMode && impl->renderMode == pl::graphics::RenderMode::wireframe)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}



	void Renderer::setUniformValues(
		pl::Renderer::Implementation *impl,
		pl::utils::Id pipeline,
		const std::string &uboName,
		const std::vector<pl::graphics::UniformFieldValue> &values
	)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto pipelineObject {static_cast<pl::impl::opengl::Pipeline*> (pl::impl::opengl::getObject(
			internalState->objects, pipeline, pl::utils::ObjectType::pipeline
		).get())};
		pipelineObject->getUbo(uboName)->setValues(values);
	}



	void Renderer::bindTexture(
		pl::Renderer::Implementation *impl,
		pl::utils::Id,
		pl::utils::Id texture,
		int bindingPoint
	)
	{
		if (texture == 0)
		{
			glBindTexture(GL_TEXTURE_2D, 0);
			return;
		}

		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto textureObject {static_cast<pl::impl::opengl::Texture*> (pl::impl::opengl::getObject(
			internalState->objects, texture, pl::utils::ObjectType::texture
		).get())};

		textureObject->bind(bindingPoint);
	}



	void Renderer::useFramebuffer(pl::Renderer::Implementation *impl, pl::utils::Id framebuffer)
	{
		if (framebuffer == 0)
		{
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
			return;
		}

		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto framebufferObject {static_cast<pl::impl::opengl::Framebuffer*> (pl::impl::opengl::getObject(
			internalState->objects, framebuffer, pl::utils::ObjectType::framebuffer
		).get())};
		framebufferObject->use();
	}



	pl::utils::Id Renderer::getFramebufferTexture(pl::Renderer::Implementation *impl, pl::utils::Id framebuffer)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto framebufferObject {static_cast<pl::impl::opengl::Framebuffer*> (pl::impl::opengl::getObject(
			internalState->objects, framebuffer, pl::utils::ObjectType::framebuffer
		).get())};
		return framebufferObject->getTextureID();
	}



	void Renderer::setRenderMode(pl::Renderer::Implementation *impl, pl::graphics::RenderMode renderMode)
	{
		impl->renderMode = renderMode;

		if (renderMode == pl::graphics::RenderMode::normal)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
			glEnable(GL_BLEND);
		}

		else if (renderMode == pl::graphics::RenderMode::wireframe)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glDisable(GL_BLEND);
		}
	}



} // namespace pl::impl::opengl
