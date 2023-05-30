#pragma once
#include "Component.h"

namespace Coa {
    template<typename T>
	struct ComponentEntity {

		template<typename ...Args>
		ComponentEntity(EntityID ent, Args&&... args) 
			: component(std::forward<Args>(args)...) { entities.push_back(ent); }

		ComponentEntity(const ComponentEntity&) = delete;
		ComponentEntity& operator=(const ComponentEntity&) = delete;

		ComponentEntity(ComponentEntity&& other) noexcept :
			entities(std::move(other.entities)), component(std::move(other.component)) 
		{
			// Empty constructor body
		}

		ComponentEntity& operator=(ComponentEntity&& other) noexcept
		{
			entities = std::move(other.entities);
			component = std::move(other.component);
			return *this;
		}

		~ComponentEntity() = default;

		T component;
		std::vector<EntityID> entities;
	};
}