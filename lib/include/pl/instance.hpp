#pragma once

#include <string>

#include "pl/blockFactory.hpp"
#include "pl/core.hpp"
#include "pl/window.hpp"



namespace pl {
	class PL_CORE Instance final {
		public:
			struct CreateInfos {
				std::string presentationName;
				pl::Vec2i viewportSize;
				pl::ByteCount blockHeapSize;
			};

			Instance(const pl::Instance::CreateInfos &createInfos);
			~Instance();

			template <typename T, typename CreateInfos>
			inline pl::Reference<T> createBlock(const CreateInfos &createInfos) {
				return m_blockFactory.create<T> (createInfos);
			}

			inline pl::Window &getWindow() const noexcept {return *m_window;}

		private:
			pl::BlockFactory m_blockFactory;
			pl::Window *m_window;
	};

} // namespace pl

