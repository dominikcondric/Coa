#pragma once
#include "ConsistentComponentVector.h"
#include <algorithm>
#include "Cala/Utility/Logger.h"
#include "Entity.h"

namespace Coa {
	template<class T>
	inline T& Scene::getComponent(EntityID entityID)
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");

		ComponentID componentID = componentDB.getComponentID<T>();
		assert(componentID != -1 && hasComponent<T>(entityID) && "Component doesn't exist!");

		ConsistentComponentVector<T>& components = componentDB.getComponentList<T>();
		return components[entityComponentTable.at(entityID).componentsIndices[componentID]].component;
	}

	template<class T>
	inline const T& Scene::getComponent(EntityID entityID) const
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");

		ComponentID componentID = componentDB.getComponentID<T>();
		assert(componentID != -1 && hasComponent<T>(entityID) && "Component doesn't exist!");

		const ConsistentComponentVector<T>& components = componentDB.getComponentList<T>();
		return components.vector[entityComponentTable.at(entityID).componentsIndices[componentID]].component;
	}

	template<class T>
	inline IterableVector<EntityID> Scene::getComponentEntityList() const
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");
		
		ComponentID compID = componentDB.getComponentID<T>();
		return IterableVector<EntityID>(componentDB.getComponentEntityList<T>());
	}

	template<class T, typename ...Args>
	inline void Scene::addComponent(EntityID entityID, Args&& ...args)
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");

		ComponentID componentID = componentDB.getComponentID<T>();
		if (componentID != -1 && hasComponent<T>(entityID))
		{
			Cala::Logger::getInstance().logErrorToConsole("Entity already has requested component!");
			return;
		}

		// Adding new component and entity to per-component entity list
		ConsistentComponentVector<T>& components = componentDB.getComponentList<T>();
		std::vector<EntityID>& componentEntityList = componentDB.getComponentEntityList<T>();
		components.emplaceBack(entityID, std::forward<Args>(args)...);

		componentID = componentDB.getComponentID<T>();

		// Adding entity to component table
		componentEntityList.push_back(entityID);
		std::sort(componentEntityList.begin(), componentEntityList.end());

		// Modifying entity component table
		entityComponentTable.at(entityID).componentsBitset.set(componentID, true);
		entityComponentTable.at(entityID).componentsIndices[componentID] = (ComponentIndex)(components.size() - 1);
	}

	template<class T, typename ...Args>
	inline T& Scene::addAndReturnComponent(EntityID entityID, Args&& ...args)
	{
		addComponent<T>(entityID, std::forward<Args>(args)...);
		return getComponent<T>(entityID);
	}

	template<class T>
	inline void Scene::shareComponent(EntityID sharingEntityID, EntityID receivingEntityID)
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");

		ComponentID componentID = componentDB.getComponentID<T>();
		if(componentID == -1 || !hasComponent<T>(sharingEntityID))
		{
			Cala::Logger::getInstance().logErrorToConsole("Sharing entity doesn't have requested component!");
			return;
		}

		if(hasComponent<T>(receivingEntityID))
		{
			Cala::Logger::getInstance().logErrorToConsole("Receiving entity already has requested component!");
			return;
		}

		// Modifying entity component table
		ComponentIndex sharingComponentIndex = entityComponentTable[sharingEntityID].componentsIndices[componentID];
		entityComponentTable[receivingEntityID].componentsBitset.set(componentID, true);
		entityComponentTable[receivingEntityID].componentsIndices[componentID] = sharingComponentIndex;

		// Adding entity to per-component entities list
		ConsistentComponentVector<T>& components = componentDB.getComponentList<T>();
		components[sharingComponentIndex].entities.push_back(receivingEntityID);
		std::sort(components[sharingComponentIndex].entities.begin(), components[sharingComponentIndex].entities.end());

		// Adding entity to component entity list
		std::vector<EntityID>& componentEntityList = componentDB.getComponentEntityList<T>();
		componentEntityList.push_back(receivingEntityID);
		std::sort(componentEntityList.begin(), componentEntityList.end());
	}

	template<class T>
	inline bool Scene::hasComponent(EntityID entityID) const
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");
		assert(entityExists(entityID));

		const auto& entCompTable = entityComponentTable.at(entityID).componentsBitset;
		return componentDB.getComponentID<T>() != -1 && entCompTable.test(componentDB.getComponentID<T>());
	}

	template<class T>
	inline void Scene::removeComponent(EntityID entityID)
	{
		static_assert(std::is_base_of<Component, T>(), "T is not derived from Component!");
		static_assert(!std::is_abstract<T>(), "T is abstract!");

		ComponentID componentID = componentDB.getComponentID<T>();
		if (componentID == -1 || !hasComponent<T>(entityID))
			return;

		ConsistentComponentVector<T>& components = componentDB.getComponentList<T>();
		ComponentIndex componentIndex = entityComponentTable.at(entityID).componentsIndices[componentID];

		// Erasing entity from per-component entity list
		std::vector<EntityID>& componentEntities = components[componentIndex].entities; // all entities sharing this component
		componentEntities.erase(std::lower_bound(componentEntities.begin(), componentEntities.end(), entityID));

		// Erasing entity from component entity list
		std::vector<EntityID>& componentEntityList = componentDB.getComponentEntityList<T>();
		componentEntityList.erase(std::lower_bound(componentEntityList.begin(), componentEntityList.end(), entityID));

		if (componentEntities.empty())
		{
			// If there are no more entities per component, erase the component
			components.erase(componentIndex);
			 
			// Adjust per-entity component indices for swapped component if neccessary
			if (!components.empty() && (std::size_t)componentIndex != components.size())
			{
				for (EntityID entity : components[componentIndex].entities)
				{
					entityComponentTable.at(entity).componentsIndices[componentID] = componentIndex;
				}
			}
		}

		// Modifying entity component table
		entityComponentTable.at(entityID).componentsBitset.set(componentID, false);
		entityComponentTable.at(entityID).componentsIndices[componentID] = -1;
	}

	template<typename T>
	inline void Scene::addOtherSceneComponent(Entity newEntity, Entity entity)
	{
		if (entity.hasComponent<T>())
		{
			if (!newEntity.hasComponent<T>())
			{
				newEntity.addComponent<T>() = std::move(entity.getComponent<T>());
			}
			else
			{
				newEntity.getComponent<T>() = std::move(entity.getComponent<T>());
			}
		}
	}
}