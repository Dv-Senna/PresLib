#pragma once

#include "pl/types.hpp"



namespace pl {
	template <bool hasCustomState>
	struct BlockImplementation;

	struct _BlockState {
		pl::BlockImplementation<true> *parent {nullptr};
		pl::Vec3f position {0.f, 0.f, 0.f};
		pl::Vec4f rotation {0.f, 0.f, 0.f, 0.f};
		pl::Vec3f zoom {1.f, 1.f, 1.f};
	};

	template <>
	class BlockImplementation<true> {
		public:
			BlockImplementation() = default;
			virtual ~BlockImplementation() = default;

			virtual const pl::_BlockState &getState() const noexcept = 0;

			virtual void move(const pl::Vec3f &offset) = 0;
			virtual void rotate(const pl::Vec3f &axis, pl::Float angle) = 0;
			virtual void zoom(const pl::Vec3f &zoom) = 0;

			virtual void setPosition(const pl::Vec3f &position) = 0;
			virtual void setRotation(const pl::Vec3f &axis, pl::Float angle) = 0;
			virtual void setZoom(const pl::Vec3f &zoom) = 0;
	};

	template <>
	class BlockImplementation<false> : public pl::BlockImplementation<true> {
		public:
			using State = pl::_BlockState;

			BlockImplementation() = default;
			virtual ~BlockImplementation() override = default;

			inline const pl::_BlockState &getState() const noexcept override;

			inline void move(const pl::Vec3f &offset) override;
			inline void rotate(const pl::Vec3f &axis, pl::Float angle) override;
			inline void zoom(const pl::Vec3f &zoom) override;

			inline void setPosition(const pl::Vec3f &position) override;
			inline void setRotation(const pl::Vec3f &axis, pl::Float angle) override;
			inline void setZoom(const pl::Vec3f &zoom) override;

		protected:
			pl::_BlockState m_state;
	};


	using Block = pl::BlockImplementation<false>;

} // namespace pl


#include "pl/block.inl"