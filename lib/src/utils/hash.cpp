#include "pl/utils/hash.hpp"

#include <string>

#include "pl/render/pipeline.hpp"
#include "pl/render/shader.hpp"
#include "pl/render/vertexLayout.hpp"



namespace pl::utils {
	template <>
	pl::Hash hash<std::string> (const std::string &value) {
		pl::Hash hash {};
		for (pl::Count i {0}; i < value.size(); ++i)
			hash ^= value[i] << i;
		return hash;
	}


	template <>
	pl::Hash hash<pl::render::Pipeline::CreateInfos> (const pl::render::Pipeline::CreateInfos &value) {
		pl::Hash hash {
			(pl::Hash)value.state.blendMode
			^ ((pl::Hash)value.state.faceCulling << 1)};
		for (pl::Count i {0}; i < value.state.shaders.size(); ++i)
			hash ^= value.state.shaders[i]->getHash() << 2 << i;
		return hash;
	}


	template <>
	pl::Hash hash<pl::render::Shader::CreateInfos> (const pl::render::Shader::CreateInfos &value) {
		pl::Hash hash {
			(pl::Hash)value.stage
			^ (pl::utils::hash<std::string> (value.path.string()) << 1)
			^ (pl::utils::hash<std::string> (value.entryPoint) << 2)
		};
		return hash;
	}


	template <>
	pl::Hash hash<pl::render::VertexLayout::CreateInfos> (const pl::render::VertexLayout::CreateInfos &value) {
		pl::Hash hash {
			(pl::Hash)value.binding
			^ ((pl::Hash)value.rate << 1)
		};
		for (pl::Count i {0}; i < value.components.size(); ++i) {
			hash ^= (pl::Hash)value.components[i].location   << 2 << i;
			hash ^= (pl::Hash)value.components[i].dimension  << 3 << i;
			hash ^= (pl::Hash)value.components[i].type       << 4 << i;
			hash ^= (pl::Hash)value.components[i].isPosition << 5 << i;
		}
		return hash;
	}

} // namespace pl::utils
