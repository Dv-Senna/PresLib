#pragma once

#include "block.hpp"


namespace pl::impl
{
	class Group : public pl::impl::Block
	{
		public:
			inline Group(pl::impl::Instance *instance) : pl::impl::Block(instance) {}
			virtual ~Group() = default;

			virtual void render() {this->m_renderChildren();}
			virtual inline void setState(const std::any &) {}
			virtual inline std::any getState() const noexcept {return m_instance;}
	};

} // namespace pl::impl
