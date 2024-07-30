#pragma once

#include <any>
#include <map>
#include <string>
#include <vector>

#include "pl/core.hpp"
#include "pl/types.hpp"



namespace pl::render {
	enum class UniformComponentType {
		eFloat32,
		eVec2f,
		eVec3f,
		eVec4f,
		eMat2f,
		eMat3f,
		eMat4f
	};

	struct UniformComponentLayout {
		std::string name;
		pl::render::UniformComponentType type;
	};

	struct UniformComponentValue {
		std::string name;
		std::any value;
	};

	struct UniformComponentMemoryLayout {
		pl::render::UniformComponentType type;
		pl::ByteCount start;
		pl::ByteCount size;
	};

	class PL_CORE Uniform final {
		public:
			struct CreateInfos {
				std::vector<pl::render::UniformComponentLayout> components;
			};

			Uniform(const pl::render::Uniform::CreateInfos &createInfos);
			~Uniform();

			void write(const std::vector<pl::render::UniformComponentValue> &components);

			inline const pl::Uint32 &getBuffer() const noexcept {return m_buffer;}

		private:
			pl::Uint32 m_buffer;
			std::map<std::string, pl::render::UniformComponentMemoryLayout> m_memoryLayout;
	};

} // namespace pl::render
