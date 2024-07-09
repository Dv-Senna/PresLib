#include "pl/block.hpp"



namespace pl {
	const pl::_BlockState &BlockImplementation<false>::getState() const noexcept {
		return m_state;
	}


	void BlockImplementation<false>::move(const pl::Vec3f &offset) {
		m_state.position += offset;
	}


	void BlockImplementation<false>::rotate(const pl::Vec3f &axis, pl::Float angle) {
		pl::Float initialSin {sinf(m_state.rotation.w * 0.5f)};
		pl::Float initialCos {cosf(m_state.rotation.w * 0.5f)};
		pl::Vec3f initialAxis {m_state.rotation.x, m_state.rotation.y, m_state.rotation.z};
		pl::Vec3f initialNormalizedAxis {initialSin * initialAxis};

		pl::Float offsetSin {sinf(angle * 0.5f)};
		pl::Float offsetCos {cosf(angle * 0.5f)};
		pl::Vec3f offsetNormalizedAxis {offsetSin * axis};

		pl::Float finalAngle {2.f * acosf(offsetCos * initialCos - pl::dot(offsetNormalizedAxis, initialNormalizedAxis))};
		pl::Vec3f finalAxis { 
			(offsetCos * initialNormalizedAxis + initialCos * offsetNormalizedAxis + pl::cross(offsetNormalizedAxis, initialNormalizedAxis))
			/ (cosf(finalAngle * 0.5f))
		};

		m_state.rotation = pl::Vec4f(finalAxis, finalAngle);
	}


	void BlockImplementation<false>::zoom(const pl::Vec3f &zoom) {
		m_state.zoom *= zoom;
	}


	void BlockImplementation<false>::setPosition(const pl::Vec3f &position) {
		m_state.position = position;
	}


	void BlockImplementation<false>::setRotation(const pl::Vec3f &axis, pl::Float angle) {
		m_state.rotation = pl::Vec4f(axis, angle);
	}


	void BlockImplementation<false>::setZoom(const pl::Vec3f &zoom) {
		m_state.zoom = zoom;
	}


} // namespace pl
