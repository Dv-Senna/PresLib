#pragma once

#include <array>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::blocks {
	class PL_CORE Triangle final : public pl::Block {
		public:
			struct CreateInfos {
				pl::Vec2f position;
				std::array<pl::Vec2f, 3> vertices;
				pl::Vec3f color;
			};

			Triangle(const pl::blocks::Triangle::CreateInfos &createInfos);
			~Triangle() override;

			void compile(pl::Instance *instance) override;

		private:
			pl::Instance *m_instance;
			pl::render::Shader *m_vertexShader;
			pl::render::Shader *m_fragmentShader;
	};

} // namespace pl::blocks
