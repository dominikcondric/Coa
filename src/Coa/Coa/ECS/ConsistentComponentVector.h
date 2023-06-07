#pragma once
#include "Coa/Utility/ConsistentVector.h"
#include "Components/ComponentEntity.h"
#include <typeinfo>
#include "TypeAliases.h"

namespace Coa {
	template<class T> class ConsistentComponentVector;
	class ComponentDatabase;
	class Scene;
	class Entity;

	class BaseConsistentComponentVector {
	public:
		using RemoveComponentFunction = void (Scene::*)(EntityID);
		using AddOtherSceneComponentFunction = void (Scene::*)(Entity, Entity);

	public:
		BaseConsistentComponentVector() = default;
		virtual ~BaseConsistentComponentVector() = default;
		virtual std::vector<EntityID>& getComponentEntityList(ComponentIndex index) = 0;
		virtual RemoveComponentFunction getRemoveComponentFunctionPointer() const = 0;
		virtual AddOtherSceneComponentFunction getAddOtherSceneComponentFunctionPointer() const = 0;
	};

	template<typename T>
	class ConsistentComponentVector : public BaseConsistentComponentVector, public ConsistentVector<ComponentEntity<T>> {
	public:
		ConsistentComponentVector() = default;
		~ConsistentComponentVector() override = default;
		ConsistentComponentVector(ConsistentComponentVector&& other) noexcept = default;
		ConsistentComponentVector& operator=(ConsistentComponentVector&& other) noexcept = default;

		std::vector<EntityID>& getComponentEntityList(ComponentIndex componentIndex) override
		{
			return ConsistentVector<ComponentEntity<T>>::data[componentIndex].entities;
		}

		RemoveComponentFunction getRemoveComponentFunctionPointer() const override
		{
			return &Scene::removeComponent<T>;
		}

		AddOtherSceneComponentFunction getAddOtherSceneComponentFunctionPointer() const override
		{
			return &Scene::addOtherSceneComponent<T>;
		}
	};
}