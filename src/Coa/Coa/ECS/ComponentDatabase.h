#pragma once
#include <unordered_map>
#include <typeinfo>
#include "TypeAliases.h"
#include <memory>

namespace Coa {
	class BaseConsistentComponentVector;
	template<typename T> class ConsistentComponentVector;

	class ComponentDatabase {
	public:
		ComponentDatabase() = default;
		~ComponentDatabase() = default;

		template<typename T> ConsistentComponentVector<T>& getComponentList();
		template<typename T> std::vector<EntityID>& getComponentEntityList();
		template<typename T> ComponentID getComponentID();

		std::vector<EntityID>& getComponentEntityListByID(ComponentID compID)
		{
			return componentEntityList[compID];
		}

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
		return *dynamic_cast<ConsistentComponentVector<T>*>(componentList[getComponentID<T>()].get());
	}

	template<typename T>
	inline std::vector<EntityID>& ComponentDatabase::getComponentEntityList()
	{
		return componentEntityList[getComponentID<T>()];
	}

	template<typename T>
	inline ComponentID ComponentDatabase::getComponentID()
	{
		const auto componentsMapIterator = componentIDMap.find(typeid(T).hash_code());
		ComponentID compID;
		if (componentsMapIterator != componentIDMap.end())
		{
			compID = componentsMapIterator->second;
		}
		else
		{
			compID = (ComponentID)componentList.size();
			componentIDMap.insert(std::make_pair(typeid(T).hash_code(), compID));
			componentList.emplace_back(std::make_unique<ConsistentComponentVector<T>>());
			componentEntityList.emplace_back();
		}

		return compID;
	}
}
