#pragma once

#include <filesystem>

#include "pl/block.hpp"
#include "pl/core.hpp"
#include "pl/render/shader.hpp"
#include "pl/resourceManager.hpp"
#include "pl/types.hpp"



namespace pl::blocks {
	struct Instance;

	class PL_CORE Image final : public pl::Block {
		public:
			struct CreateInfos {
				std::filesystem::path path;
				pl::Vec3f position;
				pl::Vec2f scale {1.f, 1.f};
			};

			Image(const pl::blocks::Image::CreateInfos &createInfos);
			~Image() override;

			void compile(pl::Instance *instance) override;

		private:
			pl::Instance *m_instance;
			pl::render::Shader *m_vertexShader;
			pl::render::Shader *m_fragmentShader;
			pl::Resource<pl::Image> m_image;
	};

} // namespace pl::blocks
