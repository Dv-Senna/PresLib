#pragma once

#include <vector>

#include "pl/core.hpp"
#include "pl/render/buffer.hpp"
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

			bool operator==(const pl::render::VertexLayout &layout) const noexcept;
			inline bool isValid() const noexcept {return m_vao != 0;}

			void linkBuffer(const pl::render::Buffer *buffer);
			void use();

			inline const pl::Uint32 &getVAO() const noexcept {return m_vao;}
			inline const pl::ByteCount &getStride() const noexcept {return m_stride;}


		private:
			pl::Uint32 m_binding;
			std::vector<pl::render::VertexComponentLayout> m_components;
			pl::render::VertexRate m_rate;
			pl::Hash m_hash;
			pl::Uint32 m_vao;
			pl::ByteCount m_stride;
			const pl::render::Buffer *m_linkedBuffer;
	};

} // namespace pl::render
