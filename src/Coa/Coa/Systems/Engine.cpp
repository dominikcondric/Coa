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
            systems.insert(systems.begin() + priority, system);
        }
        else
        {
            systems.push_back(system);
        }
    }
}