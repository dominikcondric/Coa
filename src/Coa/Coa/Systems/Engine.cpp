#include "Engine.h"

namespace Coa {
    void Engine::run(Scene &scene)
    {
        for (auto& system : systems)
        {
            system->run(scene);
        }
    }

    void Engine::addSystem(ISystem *system, uint32_t priority)
    {
        if (priority < systems.size())
        {
            systems.emplace(systems.begin() + priority, system);
        }
        else
        {
            systems.emplace_back(system);
        }
    }
}