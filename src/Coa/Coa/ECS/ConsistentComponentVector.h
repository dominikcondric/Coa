#pragma once
#include "Coa/Utility/ConsistentVector.h"
#include "Components.h"

namespace Coa {
	class BaseConsistentComponentVector {
	public:
		using removeComponentFunction = void(Scene::*)(EntityID);

	public:
		BaseConsistentComponentVector() = default;
		virtual ~BaseConsistentComponentVector() = default;
		virtual std::vector<EntityID>& getComponentEntityList(ComponentIndex index) = 0;
		virtual removeComponentFunction getRemoveComponentFunctionPointer() const = 0;
	};

	template<typename T>
	class ConsistentComponentVector : public BaseConsistentComponentVector, public ConsistentVector<ComponentEntity<T>> {
	public:
		ConsistentComponentVector() = default;
		~ConsistentComponentVector() override = default;

		std::vector<EntityID>& getComponentEntityList(ComponentIndex componentIndex) override
		{
			return ConsistentVector<ComponentEntity<T>>::vector[componentIndex].entities;
		}

		removeComponentFunction getRemoveComponentFunctionPointer() const override;
	};

	template<typename T>
	BaseConsistentComponentVector::removeComponentFunction ConsistentComponentVector<T>::getRemoveComponentFunctionPointer() const
	{
		return &Scene::removeComponent<T>;
	}
}