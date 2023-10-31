#include <iostream>
#include <list>
#include <map>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "config.hpp"
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
			UniformsBuffer(GLuint program, const pl::graphics::UniformsFormat &formats, const std::string &name, int bindingPoint) : 
				m_ubo {0},
				m_fieldsInfos {},
				m_bufferSize {0}
			{
				static std::map<pl::graphics::UniformFieldType, pl::impl::opengl::UniformsBuffer::FieldAlignement> fieldAlignments {
					{pl::graphics::UniformFieldType::floating, {4, 4}},
					{pl::graphics::UniformFieldType::integer, {4, 4}},
					{pl::graphics::UniformFieldType::vec2, {8, 4}},
					{pl::graphics::UniformFieldType::vec3, {16, 4}},
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

					glUniformBlockBinding(program, glGetUniformBlockIndex(program, name.c_str()), bindingPoint);
					glBindBufferBase(GL_UNIFORM_BUFFER, bindingPoint, m_ubo);

				glBindBuffer(GL_UNIFORM_BUFFER, 0);
			}


			~UniformsBuffer()
			{
				glDeleteBuffers(1, &m_ubo);
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
				m_size {infos.size}
			{
				static std::map<pl::graphics::TextureFormat, pl::impl::opengl::Texture::FormatValues> formats {
					{pl::graphics::TextureFormat::r8g8b8, {24, GL_RGB8, GL_RGB}},
					{pl::graphics::TextureFormat::r8g8b8a8, {32, GL_RGBA8, GL_RGBA}},
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
				glBindTexture(GL_TEXTURE_2D, m_texture);

					glTexImage2D(
						GL_TEXTURE_2D,
						0,  formats[infos.format].internalFormat,
						m_size.x, m_size.y,
						0, formats[infos.format].format, GL_UNSIGNED_BYTE, infos.pixels.get()
					);
					glGenerateMipmap(GL_TEXTURE_2D);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilters[infos.minFilter]);
					glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilters[infos.magFilter]);

				glBindTexture(GL_TEXTURE_2D, 0);
			}


			void bind(int bindingPoint)
			{
				glActiveTexture(GL_TEXTURE0 + bindingPoint);
				glBindTexture(GL_TEXTURE_2D, m_texture);
			}


			void unbind()
			{
				glBindTexture(GL_TEXTURE_2D, 0);
			}


			~Texture()
			{
				glDeleteTextures(1, &m_texture);
			}


		private:
			GLuint m_texture;
			glm::vec2 m_size;
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

		
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
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
		pl::utils::Id id {0};

		switch (type)
		{
			case pl::utils::ObjectType::vertices:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Vertices))
					throw std::runtime_error("PL : OpenGL can't register vertices because data is not valid");

				const auto &vertices {std::any_cast<pl::graphics::Vertices> (data)};
				id = pl::utils::generateNewID(idType);
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Vertices> (vertices.format, vertices.data),
					id,
					idType
				});

				break;
			}

			case pl::utils::ObjectType::shader:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Shader))
					throw std::runtime_error("PL : OpenGL can't register shader because data is not valid");

				const auto &shader {std::any_cast<pl::graphics::Shader> (data)};
				std::vector<unsigned char> fileContent {pl::utils::getBinaryFileContent(shader.file)};
				id = pl::utils::generateNewID(idType);
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Shader> (fileContent, shader.entryPoint, shader.type),
					id,
					idType
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
				
				id = pl::utils::generateNewID(idType);
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Pipeline> (shaders, pipeline.uniforms),
					id,
					idType
				});

				break;
			}

			case pl::utils::ObjectType::texture:
			{
				if (!data.has_value() || data.type() != typeid(pl::graphics::Texture))
					throw std::runtime_error("PL : OpenGL can't register texture because data is not valid");

				const auto &texture {std::any_cast<pl::graphics::Texture> (data)};
				id = pl::utils::generateNewID(idType);
				internalState->objects.push_back({
					type,
					std::make_shared<pl::impl::opengl::Texture> (texture),
					id,
					idType
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



	void Renderer::drawVertices(pl::Renderer::Implementation *impl, pl::utils::Id vertices)
	{
		auto internalState {pl::impl::opengl::checkInternalStateValidity(impl->internalState)};

		auto verticesObject {static_cast<pl::impl::opengl::Vertices*> (pl::impl::opengl::getObject(
			internalState->objects, vertices, pl::utils::ObjectType::vertices
		).get())};
		verticesObject->draw();
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



} // namespace pl::impl::opengl
