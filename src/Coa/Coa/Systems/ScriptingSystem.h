#pragma once
#include "ISystem.h"
#include "Cala/Utility/IIOSystem.h"

namespace Coa {
    class ScriptingSystem : public ISystem {
    public:
        ScriptingSystem(const Cala::IIOSystem& _io) : io(_io) {}
        ~ScriptingSystem() = default;
        void run(Scene& scene) override;
        void setDeltaTime(float newDeltaTime) { deltaTime = newDeltaTime; }

    private:
        const Cala::IIOSystem& io;
        float deltaTime;
    };
}