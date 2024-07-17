#pragma once

#include <vector>

#include "pl/render/pipeline.hpp"
#include "pl/render/vertexLayout.hpp"
#include "pl/types.hpp"



namespace pl::render {
	struct Descriptor {
		pl::render::VertexLayout *vertexLayout;
		pl::render::Pipeline *pipeline;

		bool operator==(const pl::render::Descriptor &descriptor);
	};

} // namespace pl::render
