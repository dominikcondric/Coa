#include "Scene.h"
#include "ConsistentComponentVector.h"
#include "Entity.h"
#include "Components.h"
#include <glm/gtc/random.hpp>
#include <iostream>

namespace Coa {
	Entity Scene::addEntity(const std::string& entTag, EntityID parentEntityID)
	{
		EntityID entityID;
		do {
			entityID = glm::linearRand<int>(0, INT_MAX);
		} while (entityExists(entityID));

		std::array<ComponentIndex, MAX_COMPONENTS> componentIndexArray;
		componentIndexArray.fill(-1);
		entityComponentTable.insert( { entityID, { 0, componentIndexArray } } );

		if (!entTag.empty())
			addComponent<TagComponent>(entityID, entTag);
		else
			addComponent<TagComponent>(entityID, "Entity #" + std::to_string(entityID));

		addComponent<TransformComponent>(entityID);


		Entity newEntity(this, entityID);
		entityVector.push_back(newEntity);
		auto lastElementInsertionSort = [&newEntity](std::vector<Entity>& vector) {
			uint32_t j = (uint32_t)vector.size() - 1;
			while (j > 0 && vector[j - 1].getEntityID() > newEntity.getEntityID())
			{
				vector[j] = vector[j - 1];
				j--;
			}

			vector[j] = newEntity;
		};
		
		lastElementInsertionSort(entityVector);

		if (parentEntityID != -1 && entityComponentTable.find(parentEntityID) != entityComponentTable.end())
		{
			entityComponentTable.at(parentEntityID).childrenIDs.insert(entityID);
			entityComponentTable.at(entityID).parentID = parentEntityID;
		}

		return newEntity;
	}

	void Scene::removeEntity(EntityID entityID)
	{
		if (!entityExists(entityID))
			return;

		EntityEntry& entityEntry = entityComponentTable.at(entityID);

		if (entityEntry.parentID != -1)
		{
			entityComponentTable.at(entityEntry.parentID).childrenIDs.erase(entityID);
		}

		for (EntityID childrenIDs : entityEntry.childrenIDs)
		{
			removeEntity(childrenIDs);
		}

		for (ComponentID i = 0; i < MAX_COMPONENTS; i++)
		{
			if (entityEntry.componentsBitset.test(i))
			{
				(this->*componentDB.getBaseComponentVectorByID(i).getRemoveComponentFunctionPointer())(entityID);
			}
		}

		entityComponentTable.erase(entityID);

		std::vector<Entity>::const_iterator elementToRemove;
		elementToRemove = std::lower_bound(entityVector.begin(), entityVector.end(), Entity(this, entityID), 
			[] (const Entity& e1, const Entity& e2) {
				return e1.getEntityID() < e2.getEntityID();
			}
		);
		entityVector.erase(elementToRemove);
	} 

	void Scene::clearEntities()
	{
		if (!entityComponentTable.empty())
		{
			for (int i = entityComponentTable.size() - 1; i >= 0; --i)
			{
				removeEntity(i);
			}
		}
	}

	bool Scene::entityExists(EntityID entityID) const
	{
		return entityComponentTable.find(entityID) != entityComponentTable.end();
	}

    const std::unordered_set<EntityID>& Scene::getEntityChildren(EntityID entityID) const
    {
		assert(entityExists(entityID));

		return entityComponentTable.at(entityID).childrenIDs;
    }

    const EntityID Scene::getEntityParent(EntityID entityID) const
    {
        if (!entityExists(entityID))
			return -1;

		return entityComponentTable.at(entityID).parentID;
    }
}