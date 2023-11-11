#pragma once

#include <list>
#include <memory>
#include <string>

#include "block.hpp"


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

			void draw(const glm::mat4 &globalTransformation);
			void registerBlock(std::shared_ptr<pl::Block> block);


		protected:
			Slide(const pl::Slide::CreateInfo &createInfos);

			std::list<std::shared_ptr<pl::Block>> m_blocks;
	};

} // namespace pl
