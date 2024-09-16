#pragma once

#include <map>
#include <vector>

#include "pl/render/pipeline.hpp"
#include "pl/render/texture.hpp"
#include "pl/render/uniform.hpp"
#include "pl/render/vertexLayout.hpp"
#include "pl/types.hpp"



namespace pl::render {
	struct Descriptor {
		pl::render::VertexLayout *vertexLayout;
		pl::render::Pipeline *pipeline;
		std::map<pl::Uint32, const pl::render::Texture*> textures;
		std::map<pl::Uint32, const pl::render::Uniform*> uniforms;

		bool operator==(const pl::render::Descriptor &descriptor);
	};

} // namespace pl::render
