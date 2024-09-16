#pragma once

#include <vector>

#include <entt/entt.hpp>

#include "pl/result.hpp"
#include "pl/types.hpp"



namespace pl {
	class Entity final {
		public:
			inline Entity();
			inline ~Entity();

			inline Entity(entt::registry &registry);

			inline Entity(pl::Entity &&entity);
			inline const pl::Entity &operator=(pl::Entity &&entity);

			template <typename T, typename ...Args>
			inline T &addComponent(Args ...args) const noexcept;

			template <typename T>
			inline T &getComponent() const noexcept;

			inline const entt::entity &getEntity() const noexcept {return m_entity;}

		private:
			entt::registry *m_registry;
			entt::entity m_entity;
	};

} // namespace pl


#include "pl/entity.inl"