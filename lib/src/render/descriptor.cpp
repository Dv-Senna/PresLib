#include "pl/render/descriptor.hpp"



namespace pl::render {
	bool Descriptor::operator==(const pl::render::Descriptor &descriptor) {
		return *vertexLayout == *descriptor.vertexLayout
			&& *pipeline == *descriptor.pipeline
			&& textureUnits == descriptor.textureUnits;
	}

} // namespace pl::render
