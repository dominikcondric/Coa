#include "Scene.h"
#include "ConsistentComponentVector.h"
#include "Entity.h"
#include <glm/gtc/random.hpp>
#include "Components/TagComponent.h"
#include "Components/TransformComponent.h"

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

    void Scene::append(Scene& other)
    {
		/*
		 For every entity, add it to scene and remove it from other scene,
		 but do not destroy its components because it would delete their 
		 graphics handles
		*/

		std::unordered_map<EntityID, EntityID> entityIDMappings;
		for (Entity entity : other.entityVector)
		{
			// Skip entities which have a parent
			if (entity.getParent().getEntityID() != -1)
				continue;

			appendSingleEntity(entityIDMappings, other, entity);
		}
    }

	void Scene::appendSingleEntity(std::unordered_map<EntityID, EntityID>& entityIDMappings, Scene &other, Entity entity)
    {
		EntityID parentEntityID = -1;
		if (entity.getParent().getEntityID() != -1)
			parentEntityID = entityIDMappings.at(entity.getParent().getEntityID());

		Entity newEntity = addEntity("", parentEntityID);
		entityIDMappings.insert({ entity.getEntityID(), newEntity.getEntityID() });

		for (ComponentID id = 0; id < MAX_COMPONENTS; ++id)
		{
			if (other.componentDB.componentIDExists(id))
			{
				(this->*other.componentDB.getBaseComponentVectorByID(id).getAddOtherSceneComponentFunctionPointer())(newEntity, entity);
			}
		}

		for (EntityID child : entity.getChildren())
			appendSingleEntity(entityIDMappings, other, Entity(&other, child));
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