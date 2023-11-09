#pragma once

#include <string>

#include "../block.hpp"
#include "../utils/id.hpp"


namespace pl::blocks
{
	class Math final :
		public pl::Block,
		public pl::BlockWithPosition,
		public pl::BlockWithSize,
		public pl::BlockWithOrientation,
		public pl::BlockWithColor,
		public pl::BlockWithDistortion
	{
		public:
			struct CreateInfo
			{
				std::string equation;
				float fontSize;
				glm::vec2 position;
				pl::utils::Color color {pl::utils::undefined};
				pl::utils::Radians angle {0.f};
				glm::vec2 rotationCenter {0.5f, 0.5f};
				glm::mat4 distortion {1.f};
			};

			Math(pl::Instance &instance, const pl::blocks::Math::CreateInfo &CreateInfo);
			~Math();

			void draw(const glm::mat4 &globalTransformation) override;

		protected:
			static void s_load(pl::Instance &instance);
			static void s_generatePdf(const std::string &equation, float fontSize, const std::string &hash);
			static void s_convertToImage(const std::string &hash);
			static pl::utils::Id s_vertices, s_shaders[2], s_pipeline;

			pl::utils::Id m_texture;
	};

} // namespace pl::blocks
