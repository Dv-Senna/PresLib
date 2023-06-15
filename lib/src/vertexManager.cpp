#include <stdexcept>

#include "vertexManager.hpp"



namespace pl
{
	VertexManager::VertexManager() : m_vertices {}
	{
		this->addVertex("line", {0, 0, 1, 0}, 2, pl::opengl::DrawType::line);
	}



	VertexManager::~VertexManager()
	{

	}



	void VertexManager::addVertex(
		const std::string &name,
		std::vector<float> vertices,
		int dimension,
		pl::opengl::DrawType drawType
	)
	{
		m_vertices[name] = std::make_unique<pl::opengl::Vertex> (vertices, dimension, drawType);
	}



	void VertexManager::removeVertex(const std::string &name)
	{
		auto it {m_vertices.find(name)};
		if (it == m_vertices.end())
			throw std::runtime_error("PL : Can't remove vertex '" + name + "'");

		m_vertices.erase(it);
	}



	pl::opengl::Vertex &VertexManager::get(const std::string &name)
	{
		auto it {m_vertices.find(name)};
		if (it == m_vertices.end())
			throw std::runtime_error("PL : Can't find vertex '" + name + "'");

		return *it->second;
	}



} // namespace pl
