#include "ScriptingSystem.h"
#include "Coa/ECS/Components/ScriptComponent.h"

namespace Coa {
    void ScriptingSystem::run(Scene& scene)
    {
        for (auto entity : scene.getComponentEntityList<ScriptComponent>())
        {
            scene.getComponent<ScriptComponent>(entity).getScript()->execute(
                Entity(&scene, entity),
                io,
                deltaTime
            );
        }
    }
}