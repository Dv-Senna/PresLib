#pragma once

#include <map>
#include <string>
#include <vector>

#include "pl/blockFactory.hpp"
#include "pl/core.hpp"
#include "pl/slide.hpp"
#include "pl/types.hpp"
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

			void registerSlide(const std::string &name, pl::Slide *slide);
			pl::Slide *getSlide(const std::string &name);
			pl::Slide *getSlide(pl::Count index);

			template <typename T, typename CreateInfos>
			inline pl::Reference<T> createBlock(const CreateInfos &createInfos) {
				return m_blockFactory.create<T> (createInfos);
			}

			inline pl::Window &getWindow() const noexcept {return *m_window;}

		private:
			using SlideMap = std::map<std::string, pl::Slide*>;

			pl::BlockFactory m_blockFactory;
			pl::Window *m_window;
			SlideMap m_slides;
			std::vector<SlideMap::iterator> m_slidesOrder;
	};

} // namespace pl

