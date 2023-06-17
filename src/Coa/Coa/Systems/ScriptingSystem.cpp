#include "ScriptingSystem.h"
#include "Coa/ECS/Components/ScriptComponent.h"

namespace Coa {
    void ScriptingSystem::run(Scene& scene)
    {
        for (auto entity : scene.getComponentEntityList<ScriptComponent>())
        {
            const ScriptComponent& scriptComponent = scene.getComponent<ScriptComponent>(entity);
            if (scriptComponent.getScript() == nullptr)
                continue;

            scriptComponent.getScript()->execute(
                Entity(&scene, entity),
                io,
                deltaTime
            );
        }
    }
}