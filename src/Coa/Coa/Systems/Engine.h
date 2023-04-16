#pragma once
#include "ISystem.h"
#include <vector>

namespace Coa {
    class Engine {
    public:
        Engine() = default;
        ~Engine() = default;
        void run(Scene& scene);

        void addSystem(ISystem* system, uint32_t priority = 0);

    private:
        std::vector<std::unique_ptr<ISystem>> systems;
    };

    
}