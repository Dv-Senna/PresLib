#pragma once

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::components {
	struct Transform2D {
		pl::Vec2f position;
		pl::Vec2f scale;
		pl::Float rotation;

	private:
		pl::Float __padding[3];
	};


	struct Transform3D {
		pl::Vec3f position;
		pl::Vec3f scale;
		pl::Vec4f rotation;
	};


	struct Transform {
		pl::Dimension dimension;
		union {
			pl::components::Transform2D transform2D;
			pl::components::Transform3D transform3D;
		};
	};


} // namespace pl::components



namespace pl {
	template <>
	class SE_CORE BlockView<pl::components::Transform> {

	};

} // namespace pl
