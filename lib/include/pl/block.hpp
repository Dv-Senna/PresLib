#pragma once

#include <glm/glm.hpp>

#include "utils/color.hpp"
#include "utils/types.hpp"


namespace pl
{
	struct Instance;


	class Block
	{
		public:
			virtual ~Block() = default;
			virtual void draw() = 0;
		
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
			BlockWithPosition() = default;
			glm::vec2 m_position;
	};

	class BlockWithOrientation
	{
		public:
			virtual ~BlockWithOrientation() = default;
			inline void setOrientation(pl::utils::Radians angle);
			inline pl::utils::Radians getOrientation() const noexcept;

		protected:
			BlockWithOrientation() = default;
			pl::utils::Radians m_angle;
	};

	class BlockWithSize
	{
		public:
			virtual ~BlockWithSize() = default;
			inline void setSize(const glm::vec2 &size);
			inline const glm::vec2 &getSize() const noexcept;
		
		protected:
			BlockWithSize() = default;
			glm::vec2 m_size;
	};

	class BlockWithColor
	{
		public:
			virtual ~BlockWithColor() = default;
			inline void setColor(const pl::utils::Color &color);
			inline const pl::utils::Color &getColor() const noexcept;

		protected:
			BlockWithColor() = default;
			pl::utils::Color m_color;
	};

	class BlockWithDistortion
	{
		public:
			virtual ~BlockWithDistortion() = default;
			inline void setDistortion(const glm::mat4 &distortion);
			inline const glm::mat4 &getDistortion() const noexcept;

		protected:
			BlockWithDistortion() = default;
			glm::mat4 m_distortion;
	};

} // namespace pl


#include "block.inl"