#pragma once

#include <map>
#include <string>
#include <vector>

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
				pl::ByteCount objectHeapSize {1024*1024};
				pl::ByteCount resourceHeapSize {128*1024*1024};
			};

			Instance(const pl::Instance::CreateInfos &createInfos);
			~Instance();

			void mainloop();

			void registerSlide(const std::string &name, pl::Slide *slide);
			pl::Slide *getSlide(const std::string &name);
			pl::Slide *getSlide(pl::Count index);

			bool nextSlide();
			void previousSlide();

			void handleResize();

			template <typename T, typename ...Args>
			inline T *allocateObject(Args ...args) {
				return m_objectHeapManager.allocate<T> (args...);
			}

			template <typename T>
			inline void freeObject(T *obj) {
				m_objectHeapManager.free<T> (obj);
			}

			inline pl::Window &getWindow() const noexcept {return *m_window;}
			inline pl::memory::Manager &getObjectHeap() noexcept {return m_objectHeapManager;}

		private:
			void m_calculateViewportRect();

			using SlideMap = std::map<std::string, pl::Slide*>;

			pl::Window *m_window;
			SlideMap m_slides;
			std::vector<SlideMap::iterator> m_slidesOrder;
			pl::Count m_currentSlide;
			pl::memory::HeapAllocator m_objectHeapAllocator;
			pl::memory::Manager m_objectHeapManager;
			pl::Rect2i m_viewportRect;

	};

} // namespace pl

