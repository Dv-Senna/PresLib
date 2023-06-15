#pragma once

#include <vector>

#include <GL/glew.h>


namespace pl::opengl
{
	enum class DrawType
	{
		triangle = GL_TRIANGLES,
		line = GL_LINE
	};


	class Vertex
	{
		public:
			Vertex(
				std::vector<float> vertices,
				int dimension = 2,
				pl::opengl::DrawType drawType = pl::opengl::DrawType::triangle
			);
			~Vertex();

			void draw();


		private:
			std::vector<float> m_vertices;
			GLuint m_vbo, m_vao;
			int m_dimension;
			GLenum m_drawType;
	};


} // namespace pl::opengl
