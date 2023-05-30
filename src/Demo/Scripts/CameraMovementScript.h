#pragma once
#include "Coa/ECS/Components/ScriptComponent.h"

class COA_DLL CameraMovementScript : public Coa::ScriptComponent::Script {
public:
    CameraMovementScript() = default;
    ~CameraMovementScript() = default;
    void execute(Coa::Entity entity, const Cala::IIOSystem& io, float deltaTime) override;
};

extern "C" COA_DLL Coa::ScriptComponent::Script* loadCameraMovementScript()
{
    return new CameraMovementScript;
}