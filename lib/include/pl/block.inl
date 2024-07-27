#include "pl/block.hpp"



namespace pl {
	const pl::_BlockState &BlockImplementation<false>::getState() const noexcept {
		return m_state;
	}


	void BlockImplementation<false>::move(const pl::Vec2f &offset) {
		m_state.position += offset;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::rotate(pl::Float angle) {
		m_state.rotation.x += angle;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::zoom(const pl::Vec2f &zoom) {
		m_state.zoom *= zoom;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::setPosition(const pl::Vec2f &position) {
		m_state.position = position;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::setRotation(pl::Vec3f angle) {
		m_state.rotation = angle;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::setZoom(const pl::Vec2f &zoom) {
		m_state.zoom = zoom;
		m_state.hasChanged = true;
	}


	void BlockImplementation<false>::updateTransform() {
		pl::Float32 rotsin {sinf(m_state.rotation.x)};
		pl::Float32 rotcos {cosf(m_state.rotation.x)};
		pl::Vec2f rotationCenter {m_state.rotation.y, m_state.rotation.z};
		rotationCenter *= m_state.zoom;

		pl::Mat3f rotationMatrix {
			rotcos, -rotsin, 0.f,
			rotsin, rotcos,  0.f,
			0.f,    0.f,     1.f
		};

		pl::Mat3f translationMatrix {
			1.f, 0.f, m_state.position.x,
			0.f, 1.f, m_state.position.y,
			0.f, 0.f, 1.f
		};

		pl::Mat3f zoomMatrix {
			m_state.zoom.x, 0.f,            0.f,
			0.f,            m_state.zoom.y, 0.f,
			0.f,            0.f,            1.f
		};

		pl::Mat3f rotationCenterMatrix {
			1.f, 0.f, -rotationCenter.x,
			0.f, 1.f, -rotationCenter.y,
			0.f, 0.f, 1.f
		};

		pl::Mat3f inverseRotationCenterMatrix {
			1.f, 0.f, rotationCenter.x,
			0.f, 1.f, rotationCenter.y,
			0.f, 0.f, 1.f
		};

		m_state.transform = translationMatrix * inverseRotationCenterMatrix * rotationMatrix * rotationCenterMatrix * zoomMatrix;
		m_state.hasChanged = false;
	}


} // namespace pl
