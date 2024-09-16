#include "pl/entity.hpp"

#include "pl/assertation.hpp"



namespace pl {
	Entity::Entity() :
		m_registry {nullptr},
		m_entity {}
	{

	}


	Entity::~Entity() {
		if (m_registry)
			m_registry->destroy(m_entity);
	}


	Entity::Entity(entt::registry &registry) :
		m_registry {&registry},
		m_entity {}
	{
		m_entity = m_registry->create();
	}


	Entity::Entity(pl::Entity &&entity) :
		m_registry {entity.m_registry},
		m_entity {entity.m_entity}
	{
		entity.m_registry = nullptr;
		entity.m_entity = entt::entity();
	}


	const pl::Entity &Entity::operator=(pl::Entity &&entity) {
		if (m_registry)
			m_registry->destroy(m_entity);

		m_registry = entity.m_registry;
		m_entity = entity.m_entity;

		entity.m_registry = nullptr;
		entity.m_entity = entt::entity();
		return *this;
	}


	template <typename T, typename ...Args>
	T &Entity::addComponent(Args ...args) const noexcept {
		m_registry->emplace<T> (m_entity, ...args);
	}


	template <typename T>
	T &Entity::getComponent() const noexcept {
		T *component {m_registry->try_get<T> (m_entity)}
		PL_ASSERT(component != nullptr, "Can't get component of type T on block that does not have it");
		return *component;
	}


} // namespace pl