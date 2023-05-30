#pragma once
#include "ISystem.h"
#include <vector>

namespace Coa {
    class Engine {
    public:
        Engine() = default;
        ~Engine() = default;
        void run(Scene& scene);

        // Adds system to the engine, but it DOES NOT transfer ownership!
        void addSystem(ISystem* system, uint32_t priority = 0);

    private:
        std::vector<ISystem*> systems;
    };

    
}