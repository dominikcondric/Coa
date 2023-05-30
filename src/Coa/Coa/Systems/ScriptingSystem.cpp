#include "ScriptingSystem.h"
#include "Coa/ECS/Components/ScriptComponent.h"
#include <iostream>

namespace Coa {
    void ScriptingSystem::run(Scene& scene)
    {
        for (auto entity : scene.getComponentEntityList<ScriptComponent>())
        {
            scene.getComponent<ScriptComponent>(entity).executeScript(Entity(&scene, entity), io, deltaTime);
        }
    }
}