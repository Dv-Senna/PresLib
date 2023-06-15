#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "opengl/vertex.hpp"


namespace pl
{
	class VertexManager final
	{
		public:
			VertexManager();
			~VertexManager();

			void addVertex(
				const std::string &name,
				std::vector<float> vertices,
				int dimension = 2,
				pl::opengl::DrawType drawType = pl::opengl::DrawType::triangle
			);
			void removeVertex(const std::string &name);

			pl::opengl::Vertex &get(const std::string &name);

		private:
			std::unordered_map<std::string, std::unique_ptr<pl::opengl::Vertex>> m_vertices;
	};

} // namespace pl
