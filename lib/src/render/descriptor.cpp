#include "pl/render/descriptor.hpp"



namespace pl::render {
	bool Descriptor::operator==(const pl::render::Descriptor &descriptor) {
		return *vertexLayout == *descriptor.vertexLayout
			&& *pipeline == *descriptor.pipeline
			&& textures == descriptor.textures
			&& uniforms == descriptor.uniforms;
	}

} // namespace pl::render
