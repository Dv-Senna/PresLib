#include <iostream>
#include <map>

#include "impl/opengl/renderer.hpp"

#include "renderer.hpp"



namespace pl
{
	Renderer::Renderer(const pl::Renderer::CreateInfo &createInfo) : 
		m_impl {}
	{
		static const std::map<pl::graphics::Api, pl::Renderer::Functions> functions {
			{pl::graphics::Api::OpenGL, {
				pl::impl::opengl::Renderer::setup,
				pl::impl::opengl::Renderer::cleanup,
				pl::impl::opengl::Renderer::cleanViewport,
				pl::impl::opengl::Renderer::updateScreen,
				pl::impl::opengl::Renderer::registerObject,
				pl::impl::opengl::Renderer::getObjectType,
				pl::impl::opengl::Renderer::usePipeline,
				pl::impl::opengl::Renderer::drawVertices
			}}
		};

		m_impl.viewportSize = createInfo.viewportSize;
		m_impl.window = createInfo.window;

		auto it {functions.find(createInfo.graphicsApi)};
		if (it == functions.end())
			throw std::runtime_error("PL : Can't use graphics api " + std::to_string((int)createInfo.graphicsApi) + " in renderer");

		m_impl.functions = it->second;

		if (m_impl.functions.isOneNotSet())
			throw std::runtime_error("PL : One or more functions of the renderer are not set");

		m_impl.functions.setup(&m_impl, createInfo);
	}


	
	Renderer::~Renderer()
	{
		if (m_impl.functions.cleanup == nullptr)
			return;

		m_impl.functions.cleanup(&m_impl);
	}



	void Renderer::cleanViewport(const pl::utils::Color &color)
	{
		if (m_impl.functions.cleanViewport == nullptr)
			throw std::runtime_error("PL : Renderer's cleanViewport function is not defined");

		m_impl.functions.cleanViewport(&m_impl, color);
	}



	void Renderer::updateScreen()
	{
		if (m_impl.functions.updateScreen == nullptr)
			throw std::runtime_error("PL : Renderer's updateScreen function is not defined");

		m_impl.functions.updateScreen(&m_impl);
	}



	pl::utils::Id Renderer::registerObject(pl::utils::ObjectType type, const std::any &data, pl::utils::IdType idType)
	{
		if (m_impl.functions.registerObject == nullptr)
			throw std::runtime_error("PL : Renderer's registerObject function is not defined");

		return m_impl.functions.registerObject(&m_impl, type, data, idType);
	}



	pl::utils::ObjectType Renderer::getObjectType(pl::utils::Id objectID)
	{
		if (m_impl.functions.getObjectType == nullptr)
			throw std::runtime_error("PL : Renderer's getObjectType function is not defined");

		return m_impl.functions.getObjectType(&m_impl, objectID);
	}



	void Renderer::usePipeline(pl::utils::Id pipeline)
	{
		if (m_impl.functions.usePipeline == nullptr)
			throw std::runtime_error("PL : Renderer's usePipeline function is not defined");

		return m_impl.functions.usePipeline(&m_impl, pipeline);
	}



	void Renderer::drawVertices(pl::utils::Id vertices)
	{
		if (m_impl.functions.drawVertices == nullptr)
			throw std::runtime_error("PL : Renderer's drawVertices function is not defined");

		return m_impl.functions.drawVertices(&m_impl, vertices);
	}



} // namespace pl
