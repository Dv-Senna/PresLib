#include "pl/block.hpp"



namespace pl {
	const pl::_BlockState &BlockImplementation<false>::getState() const noexcept {
		return m_state;
	}


	void BlockImplementation<false>::move(const pl::Vec2f &offset) {
		m_state.position += offset;
	}


	void BlockImplementation<false>::rotate(pl::Float angle) {
		m_state.rotation.x += angle;
	}


	void BlockImplementation<false>::zoom(const pl::Vec2f &zoom) {
		m_state.zoom *= zoom;
	}


	void BlockImplementation<false>::setPosition(const pl::Vec2f &position) {
		m_state.position = position;
	}


	void BlockImplementation<false>::setRotation(pl::Vec3f angle) {
		m_state.rotation = angle;
	}


	void BlockImplementation<false>::setZoom(const pl::Vec2f &zoom) {
		m_state.zoom = zoom;
	}


} // namespace pl
