#include "LightIntensityChangeScript.h"
#include "Coa/ECS/Components/LightComponent.h"
#include <iostream>

void LightIntensityChangeScript::execute(Coa::Entity entity, const Cala::IIOSystem &io, float deltaTime)
{
    Coa::LightComponent& lightComponent = entity.getComponent<Coa::LightComponent>();
    lightComponent.intensity += deltaTime * direction * 5.f;
    if (lightComponent.intensity > 5.f || lightComponent.intensity < 0.f)
        direction *= -1.f;
}