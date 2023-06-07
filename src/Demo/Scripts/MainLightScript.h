#pragma once
#include "Coa/ECS/Components/ScriptComponent.h"

class COA_DLL MainLightScript : public Coa::ScriptComponent::Script {
public:
    MainLightScript() = default;
    ~MainLightScript() = default;
    void execute(Coa::Entity entity, const Cala::IIOSystem& io, float deltaTime) override;

private:
    float direction = 1.f;
};

extern "C" COA_DLL Coa::ScriptComponent::Script* loadMainLightScript()
{
    return new MainLightScript;
}