#pragma once

#include <map>
#include <string>
#include <vector>

#include "pl/blockFactory.hpp"
#include "pl/core.hpp"
#include "pl/memory/heapAllocator.hpp"
#include "pl/memory/manager.hpp"
#include "pl/slide.hpp"
#include "pl/types.hpp"
#include "pl/window.hpp"



namespace pl {
	class PL_CORE Instance final {
		public:
			struct CreateInfos {
				std::string presentationName;
				pl::Vec2i viewportSize;
				pl::ByteCount blockHeapSize {1024*1024};
				pl::ByteCount objectHeapSize {1024*1024};
			};

			Instance(const pl::Instance::CreateInfos &createInfos);
			~Instance();

			void mainloop();

			void registerSlide(const std::string &name, pl::Slide *slide);
			pl::Slide *getSlide(const std::string &name);
			pl::Slide *getSlide(pl::Count index);

			bool nextSlide();
			void previousSlide();

			template <typename T, typename CreateInfos>
			inline pl::Reference<T> createBlock(const CreateInfos &createInfos) {
				return m_blockFactory.create<T> (createInfos);
			}

			inline pl::Window &getWindow() const noexcept {return *m_window;}
			inline pl::memory::Manager &getObjectHeap() noexcept {return m_objectHeapManager;}

		private:
			using SlideMap = std::map<std::string, pl::Slide*>;

			pl::BlockFactory m_blockFactory;
			pl::Window *m_window;
			SlideMap m_slides;
			std::vector<SlideMap::iterator> m_slidesOrder;
			pl::Count m_currentSlide;
			pl::memory::HeapAllocator m_objectHeapAllocator;
			pl::memory::Manager m_objectHeapManager;

	};

} // namespace pl

