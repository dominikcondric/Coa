#pragma once
#include "Coa/ECS/Components/ScriptComponent.h"
#include "Cala/Rendering/GraphicsAPI.h"
#include "Coa/ECS/Scene.h"

class COA_DLL CameraMovementScript : public Coa::ScriptComponent::Script {
public:
    CameraMovementScript() = default;
    ~CameraMovementScript() = default;
    void execute(Coa::Entity entity, const Cala::IIOSystem& io, float deltaTime) override;
    void loadNewEntities(Coa::Scene& scene) override;
};

extern "C" COA_DLL Coa::ScriptComponent::Script* loadCameraMovementScript()
{
    return new CameraMovementScript;
}