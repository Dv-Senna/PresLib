#include "shaderManager.hpp"



namespace pl
{
	ShaderManager::ShaderManager() : m_shaders {}, m_current {nullptr}
	{
		this->addShader("line", "line");
		this->addShader("circle", "circle");
	}



	ShaderManager::~ShaderManager()
	{

	}



	void ShaderManager::addShader(const std::string &name, const std::string &path)
	{
		m_shaders[name] = std::make_unique<pl::opengl::Shader> (path);
	}



	pl::opengl::Shader &ShaderManager::getShader(const std::string &name)
	{
		auto it {m_shaders.find(name)};
		if (it == m_shaders.end())
			throw std::runtime_error("PL : Can't find shader '" + name + "' in shader manager");

		return *it->second;
	}



	void ShaderManager::use(const std::string &name)
	{
		auto it {m_shaders.find(name)};
		if (it == m_shaders.end())
			throw std::runtime_error("PL : Can't use shader '" + name + "' in shader manager");

		it->second->use();
		m_current = it->second.get();
	}



	pl::opengl::Shader &ShaderManager::getCurrent()
	{
		if (m_current == nullptr)
			throw std::runtime_error("PL : there is no shader currently use");

		return *m_current;
	}






} // namespace pl
