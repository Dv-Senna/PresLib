#pragma once

#include <memory>

#include "block/group.hpp"
#include "colorManager.hpp"


namespace pl
{
	class Instance;

	class Theme
	{
		public:
			Theme(pl::Instance &instance);
			virtual ~Theme();

			void use();

		protected:
			pl::Instance &m_instance;
			std::unique_ptr<pl::block::Group> m_background, m_overlay;
			pl::ColorScheme m_scheme;
	};

} // namespace pl