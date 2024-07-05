#pragma once

#include <string>

#include "pl/componentFactory.hpp"
#include "pl/core.hpp"



namespace pl {
	class PL_CORE Instance final {
		public:
			struct CreateInfos {

			};

			Instance(const pl::Instance::CreateInfos &createInfos);
			~Instance();

			template <typename T, typename CreateInfos>
			inline pl::Reference<T> createComponent(const CreateInfos &createInfos) {
				return m_componentFactory.create<T> (createInfos);
			}

		private:
			pl::ComponentFactory m_componentFactory;
	};

} // namespace pl

