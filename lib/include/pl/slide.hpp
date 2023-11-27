#pragma once

#include <list>
#include <memory>
#include <string>

#include "block.hpp"
#include "utils/id.hpp"



namespace pl
{
	class Slide final
	{
		friend class pl::Instance;

		public:
			enum class Flag
			{
				none = 0
			};

			enum class Type
			{
				normal
			};

			struct CreateInfo
			{
				pl::Slide::Type type {pl::Slide::Type::normal};
				std::string name {""};
				std::string title {""};
				pl::Slide::Flag flags {pl::Slide::Flag::none};
			};

			~Slide() = default;

			void drawBlocks();
			void draw(const glm::mat4 &globalTransformation, const pl::utils::Color &color);
			void registerBlock(std::shared_ptr<pl::Block> block);


		protected:
			Slide(pl::Instance &instance, const pl::Slide::CreateInfo &createInfos);
			static void s_load(pl::Instance &instance);

			pl::Instance &m_instance;
			std::list<std::shared_ptr<pl::Block>> m_blocks;
			pl::utils::Id m_framebuffer, m_framebufferTexture;
			static pl::utils::Id s_vertices, s_shader[2], s_pipeline;
			static glm::mat4 s_transformationMatrix;
	};

} // namespace pl
