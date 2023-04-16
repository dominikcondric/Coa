#include "Entity.h"

namespace Coa {
    Entity& Coa::Entity::operator=(const Entity& other)
    {
        scene = other.scene;
        entityID = other.entityID;
        return *this;
    }

    Entity& Coa::Entity::operator=(Entity&& other)
    {
        *this = other;
        return *this;
    }
}