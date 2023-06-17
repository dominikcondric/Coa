#include "SceneManagementSystem.h"
#include "Coa/ECS/Components/DestroyEntityComponent.h"
#include "Coa/ECS/Components/ScriptComponent.h"
#include "Coa/ECS/Entity.h"

namespace Coa {
    void SceneManagementSystem::run(Scene &scene)
    {
        Scene newScene;
        for (EntityID entity : scene.getComponentEntityList<ScriptComponent>())
        {
            ScriptComponent& scriptComponent = scene.getComponent<ScriptComponent>(entity);
            if (scriptComponent.shouldLoadNewEntities)
            {
                scriptComponent.getScript()->loadNewEntities(newScene);
                scriptComponent.shouldLoadNewEntities = false;
            }
        }

        if (newScene.getEntities().size() != 0)
            scene.append(newScene);

        std::vector<EntityID> entitiesToDestroy;
        for (EntityID entity : scene.getComponentEntityList<DestroyEntityComponent>())
        {
            const DestroyEntityComponent& destroyEntityComponent = scene.getComponent<DestroyEntityComponent>(entity);
            if (destroyEntityComponent.destroy)
                entitiesToDestroy.push_back(entity);
        }

        for (EntityID entity : entitiesToDestroy)
            scene.removeEntity(entity);
    }
}