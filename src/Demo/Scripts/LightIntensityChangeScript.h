#pragma once
#include "Coa/ECS/Components/ScriptComponent.h"

class COA_DLL LightIntensityChangeScript : public Coa::ScriptComponent::Script {
public:
    LightIntensityChangeScript() = default;
    ~LightIntensityChangeScript() = default;
    void execute(Coa::Entity entity, const Cala::IIOSystem& io, float deltaTime) override;

private:
    float direction = 1.f;
};

extern "C" COA_DLL Coa::ScriptComponent::Script* loadLightIntensityChangeScript()
{
    return new LightIntensityChangeScript;
}