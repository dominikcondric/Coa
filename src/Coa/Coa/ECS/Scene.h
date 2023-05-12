#pragma once
#include <vector>
#include "Coa/Utility/IterableVector.h"
#include "Coa/Utility/ConsistentVector.h"
#include "ComponentDatabase.h"
#include <bitset>
#include "TypeAliases.h"

namespace Coa {
	class Entity;

	class Scene {
	public:
		Scene() = default;
		~Scene() = default;
		Entity addEntity(const std::string& entTag = "");
		void removeEntity(EntityID entityID);
		void clearEntities();
		bool entityExists(EntityID entityID) const;
		IterableVector<Entity> getEntities() { return IterableVector<Entity>(entityVector); }

		template<class T> T& getComponent(EntityID entityID);
		template<class T> const T& getComponent(EntityID entityID) const;
		template<class T> IterableVector<EntityID> getComponentEntityList() const;
		template<class T, typename ...Args> void addComponent(EntityID entityID, Args&&... args);
		template<class T, typename ...Args> T& addAndReturnComponent(EntityID entityID, Args&&... args);
		template<class T> void shareComponent(EntityID sharingEntityID, EntityID receivingEntityID);
		template<class T> bool hasComponent(EntityID entityID) const;
		template<class T> void removeComponent(EntityID entityID);

	private:
		static const int MAX_COMPONENTS = 8;

		// Component managing
		mutable ComponentDatabase componentDB;

		// Entity managing
		std::unordered_map<EntityID, std::pair<std::bitset<MAX_COMPONENTS>, std::array<ComponentIndex, MAX_COMPONENTS>>> entityComponentTable;
		std::vector<Entity> entityVector;
	};
}

#include "Scene.tpp"