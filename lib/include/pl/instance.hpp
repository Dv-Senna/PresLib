#pragma once

#include <string>

#include "pl/blockFactory.hpp"
#include "pl/core.hpp"



namespace pl {
	class PL_CORE Instance final {
		public:
			struct CreateInfos {
				pl::ByteCount blockHeapSize;
			};

			Instance(const pl::Instance::CreateInfos &createInfos);
			~Instance();

			template <typename T, typename CreateInfos>
			inline pl::Reference<T> createBlock(const CreateInfos &createInfos) {
				return m_blockFactory.create<T> (createInfos);
			}

		private:
			pl::BlockFactory m_blockFactory;
	};

} // namespace pl

