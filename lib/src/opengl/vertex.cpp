#include "opengl/vertex.hpp"



namespace pl::opengl
{
	Vertex::Vertex(
		std::vector<float> vertices,
		int dimension,
		pl::opengl::DrawType drawType
	) :
		m_vertices {std::move(vertices)},
		m_vbo {},
		m_vao {},
		m_dimension {dimension},
		m_drawType {static_cast<GLenum> (drawType)}
	{
		glCreateVertexArrays(1, &m_vao);
		glBindVertexArray(m_vao);

		glCreateBuffers(1, &m_vbo);
		glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * m_vertices.size(), m_vertices.data(), GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, m_dimension, GL_FLOAT, GL_FALSE, m_dimension * sizeof(float), (void*)0);
	}



	Vertex::~Vertex()
	{
		glDeleteVertexArrays(1, &m_vao);
		glDeleteBuffers(1, &m_vbo);
	}



	void Vertex::draw()
	{
		//glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
		glBindVertexArray(m_vao);

		glDrawArrays(m_drawType, 0, m_vertices.size() / m_dimension);
	}



} // namespace pl::opengl
