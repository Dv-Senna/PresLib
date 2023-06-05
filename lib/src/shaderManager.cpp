#include "shaderManager.hpp"



namespace pl
{
	ShaderManager::ShaderManager() : m_shaders {}
	{

	}



	ShaderManager::~ShaderManager()
	{

	}



	void ShaderManager::addShader(const std::string &name, const std::string &path)
	{
		m_shaders[name] = std::make_unique<pl::Shader> (path);
	}



	pl::Shader &ShaderManager::getShader(const std::string &name)
	{
		auto it {m_shaders.find(name)};
		if (it == m_shaders.end())
			throw std::runtime_error("PL : Can't find shader '" + name + "' in shader manager");

		return *it->second;
	}



} // namespace pl
