#pragma once

#include <any>
#include <memory>

#include <glm/glm.hpp>

#include "utils/color.hpp"
#include "utils/types.hpp"


namespace pl
{
	class Instance;


	class Block
	{
		public:
			enum class Type
			{
				rectangle,
				triangle,
				group,
				line,
				ellipse,
				math
			};

			struct CreateInfo
			{
				pl::Block::Type type;
				std::any data;
			};

			virtual ~Block() = default;
			virtual void draw(const glm::mat4 &globalTransformation) = 0;
			inline virtual void registerBlock(std::shared_ptr<pl::Block> block);
		
		protected:
			inline Block(pl::Instance &instance);
			pl::Instance &m_instance;
	};


	class BlockWithPosition
	{
		public:
			virtual ~BlockWithPosition() = default;
			inline void setPosition(const glm::vec2 &position);
			inline const glm::vec2 &getPosition() const noexcept;

		protected:
			inline BlockWithPosition(const glm::vec2 &position);
			glm::vec2 m_position;
	};

	class BlockWithOrientation
	{
		public:
			virtual ~BlockWithOrientation() = default;
			inline void setOrientation(pl::utils::Radians angle);
			inline pl::utils::Radians getOrientation() const noexcept;
			inline void setRotationCenter(const glm::vec2 &rotationCenter);
			inline const glm::vec2 &getRotationCenter() const noexcept;

		protected:
			inline BlockWithOrientation(pl::utils::Radians angle, const glm::vec2 &rotationCenter);
			pl::utils::Radians m_angle;
			glm::vec2 m_rotationCenter;
	};

	class BlockWithSize
	{
		public:
			virtual ~BlockWithSize() = default;
			inline void setSize(const glm::vec2 &size);
			inline const glm::vec2 &getSize() const noexcept;
		
		protected:
			inline BlockWithSize(const glm::vec2 &size);
			glm::vec2 m_size;
	};

	class BlockWithColor
	{
		public:
			virtual ~BlockWithColor() = default;
			inline void setColor(const pl::utils::Color &color);
			inline const pl::utils::Color &getColor() const noexcept;

		protected:
			inline BlockWithColor(const pl::utils::Color &color);
			pl::utils::Color m_color;
	};

	class BlockWithDistortion
	{
		public:
			virtual ~BlockWithDistortion() = default;
			inline void setDistortion(const glm::mat4 &distortion);
			inline const glm::mat4 &getDistortion() const noexcept;

		protected:
			inline BlockWithDistortion(const glm::mat4 &distortion);
			glm::mat4 m_distortion;
	};

} // namespace pl


#include "block.inl"