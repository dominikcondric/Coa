#pragma once
#include "Scene.h"

namespace Coa {
	template<class T>
	inline bool Entity::hasComponent() const 
	{
		return scene->hasComponent<T>(entityID);
	}

	template<class T>
	inline T& Entity::getComponent() const
	{
		return scene->getComponent<T>(entityID);
	}

	template<class T>
	inline void Entity::shareComponent(const Entity& other) const
	{
		return scene->shareComponent<T>(other.entityID, entityID);
	}

	template<class T, typename ...Args>
	inline T& Entity::addComponent(Args&& ...args)
	{
		return scene->addAndReturnComponent<T>(entityID, std::forward<Args>(args)...);
	}

	template<class T>
	inline void Entity::removeComponent()
	{
		scene->removeComponent<T>(entityID);
	}
}