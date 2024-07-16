#include "pl/utils/hash.hpp"

#include <vector>

#include "pl/render/pipeline.hpp"



namespace pl::utils {
	/**
	 * This specialization uses a folding hashing method. Its purpose is just to decrease equality-check time
	 */
	template <>
	pl::Hash hash<std::vector<pl::Byte>> (const std::vector<pl::Byte> &value) {
		if (value.size() == sizeof(pl::Hash))
			return *reinterpret_cast<const pl::Hash*> (value.data());

		if (value.size() < sizeof(pl::Hash)) {
			pl::Hash output {};
			memcpy(&output, value.data(), value.size());
			pl::Hash zero {0};
			memcpy((pl::Byte*)&output + value.size(), &zero, sizeof(pl::Hash) - value.size());
			return output;
		}

		std::vector<pl::Hash> parts {};
		parts.reserve(value.size() / sizeof(pl::Hash) + 1);
		for (pl::ByteCount it {0}; it < value.size(); it += sizeof(pl::Hash)) {
			pl::ByteCount leftover = value.size() - it;

			if (leftover >= sizeof(pl::Hash)) {
				parts.push_back(*reinterpret_cast<const pl::Hash*> (value.data() + it));
				continue;
			}

			pl::Hash tmp {};
			memcpy(&tmp, value.data() + it, value.size());
			pl::Hash zero {0};
			memcpy((pl::Byte*)&tmp + value.size(), &zero, sizeof(pl::Hash) - value.size());
			parts.push_back(tmp);
			break;
		}

		pl::Hash output {0};
		for (const auto &part : parts)
			output ^= part;
		return output;
	}


	/*
	 * This specialization hash the state of a pipeline
	 */
	template <>
	pl::Hash hash<pl::render::Pipeline::State> (const pl::render::Pipeline::State &value) {
		std::vector<pl::Byte> hashData {};
		hashData.resize(sizeof(bool) + sizeof(pl::render::Shader*) * value.shaders.size());
		memcpy(hashData.data(), &value.faceCulling, sizeof(bool));
		memcpy(hashData.data() + sizeof(bool), value.shaders.data(), sizeof(pl::render::Shader*) * value.shaders.size());
		return pl::utils::hash(hashData);
	}

} // namespace pl::utils
