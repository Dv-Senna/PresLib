#pragma once

#include <vector>

#include "pl/core.hpp"
#include "pl/types.hpp"
#include "pl/utils/hash.hpp"



namespace pl::render {
	enum class VertexComponentType {
		eFloat32,
		eInt32,
		eUint32
	};

	enum class VertexRate {
		eVertex,
		eInstance
	};

	struct VertexComponentLayout final {
		pl::Uint32 location;
		pl::Uint32 dimension;
		pl::render::VertexComponentType type {pl::render::VertexComponentType::eFloat32};
	};


	class PL_CORE VertexLayout final {
		public:
			struct CreateInfos {
				pl::Uint32 binding;
				std::vector<pl::render::VertexComponentLayout> components;
				pl::render::VertexRate rate {pl::render::VertexRate::eVertex};
			};

			VertexLayout(const pl::render::VertexLayout::CreateInfos &createInfos);
			~VertexLayout();

			bool operator==(const pl::render::VertexLayout &layout);

		private:
			pl::Uint32 m_binding;
			std::vector<pl::render::VertexComponentLayout> m_components;
			pl::render::VertexRate m_rate;
			pl::Hash m_hash;
			pl::Uint32 m_vao;
			pl::ByteCount m_stride;
	};

} // namespace pl::render
