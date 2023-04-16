#pragma once
#include "Coa/ECS/Scene.h"

namespace Coa {
    class ISystem {
    public:
        ISystem() = default;
        virtual ~ISystem() = 0;
        virtual void run(Scene& scene) = 0;
    };
}