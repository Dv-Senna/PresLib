#pragma once

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::render {
	enum class BufferType {
		eVertex
	};

	enum class BufferUsage {
		eStatic,
		eDynamic
	};

	class PL_CORE Buffer final {
		public:
			struct CreateInfos {
				pl::render::BufferType type;
				pl::render::BufferUsage usage;
				pl::ByteCount size;
			};

			Buffer(const pl::render::Buffer::CreateInfos &createInfos);
			~Buffer();

			void write(pl::ByteCount offset, pl::ByteCount size, const pl::Byte *data);

			inline const pl::render::BufferType &getType() const noexcept {return m_type;}
			inline const pl::ByteCount &getSize() const noexcept {return m_size;}
			inline const pl::Uint32 &getBuffer() const noexcept {return m_buffer;}

			inline bool isValid() const noexcept {return m_buffer != 0;}

		private:
			pl::render::BufferType m_type;
			pl::render::BufferUsage m_usage;
			pl::ByteCount m_size;
			pl::Uint32 m_buffer;
	};

} // namespace pl::render
