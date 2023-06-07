#pragma once
#include "ISystem.h"
#include <unordered_map>
#include "Coa/Utility/SharedLibrary.h"

namespace Coa {
    class SceneManagementSystem : public ISystem {
    public:
        SceneManagementSystem() = default;
        ~SceneManagementSystem() = default;
        void run(Scene& scene) override;
    };
}