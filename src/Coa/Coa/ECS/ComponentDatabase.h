#pragma once
#include <unordered_map>
#include <typeinfo>
#include "TypeAliases.h"
#include <memory>
#include <vector>
#include <cassert>

namespace Coa {
	class BaseConsistentComponentVector;
	template<typename T> class ConsistentComponentVector;

	class ComponentDatabase {
	public:
		ComponentDatabase() = default;
		~ComponentDatabase() = default;

		template<typename T> ConsistentComponentVector<T>& getComponentList();
		template<typename T> std::vector<EntityID>& getComponentEntityList();
		template<typename T> ComponentID getComponentID() const;

		std::vector<EntityID>& getComponentEntityListByID(ComponentID compID)
		{
			return componentEntityList[compID];
		}

		bool componentIDExists(ComponentID componentID) const { return componentID < componentIDMap.size(); }

		BaseConsistentComponentVector& getBaseComponentVectorByID(ComponentID compID) 
		{
			assert((std::size_t)compID < componentList.size());
			return *componentList[compID]; 
		}

	private:
		std::unordered_map<std::size_t, ComponentID> componentIDMap; // Stores component identifiers (class hash codes)
		std::vector<std::unique_ptr<BaseConsistentComponentVector>> componentList; // List of component lists
		std::vector<std::vector<EntityID>> componentEntityList; // Stores entity IDs for every component type
	};

	template<typename T>
	inline ConsistentComponentVector<T>& ComponentDatabase::getComponentList()
	{
		ComponentID compID = getComponentID<T>();
		if (compID == -1)
		{
			compID = (ComponentID)componentList.size();
			componentIDMap.insert(std::make_pair(typeid(T).hash_code(), compID));
			componentList.emplace_back(std::make_unique<ConsistentComponentVector<T>>());
			componentEntityList.emplace_back();
		}

		return *dynamic_cast<ConsistentComponentVector<T>*>(componentList[compID].get());
	}

	template<typename T>
	inline std::vector<EntityID>& ComponentDatabase::getComponentEntityList()
	{
		ComponentID compID = getComponentID<T>();
		if (compID == -1)
		{
			compID = (ComponentID)componentList.size();
			componentIDMap.insert(std::make_pair(typeid(T).hash_code(), compID));
			componentList.emplace_back(std::make_unique<ConsistentComponentVector<T>>());
			componentEntityList.emplace_back();
		}

		return componentEntityList[compID];
	}

	template<typename T>
	inline ComponentID ComponentDatabase::getComponentID() const
	{
		const auto componentsMapIterator = componentIDMap.find(typeid(T).hash_code());
		if (componentsMapIterator != componentIDMap.end())
			return componentsMapIterator->second;

		return -1;
	}
}
