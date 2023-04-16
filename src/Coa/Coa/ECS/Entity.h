#pragma once 
#include <vector>
#include "TypeAliases.h"

namespace Coa {
	class Scene;

	class Entity {
	public:
		Entity(Scene* scene, EntityID entityID) : scene(scene), entityID(entityID) {}
		Entity(const Entity& other) = default;
		Entity(Entity&& other) = default;
		Entity& operator=(const Entity& other);
		Entity& operator=(Entity&& other);
		~Entity() = default;

		template<class T> bool hasComponent() const;
		template<class T> T& getComponent() const;
		template<class T, typename ...Args> T& addComponent(Args&& ...args);
		template<class T> void shareComponent(const Entity& other) const;
		template<class T> void removeComponent();
		EntityID getEntityID() const { return entityID; }
		

		bool operator==(const Entity& other) const
		{
			return entityID == other.entityID;
		}

	private:
		Scene* scene;
		EntityID entityID;
	};
}

#include "Entity.tpp"