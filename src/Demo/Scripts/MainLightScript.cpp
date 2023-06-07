#include "MainLightScript.h"
#include "Coa/ECS/Components/LightComponent.h"
#include "Coa/ECS/Components/TransformComponent.h"
#include "Coa/ECS/Components/DestroyEntityComponent.h"

void MainLightScript::execute(Coa::Entity entity, const Cala::IIOSystem &io, float deltaTime)
{
    Coa::LightComponent& lightComponent = entity.getComponent<Coa::LightComponent>();
    lightComponent.intensity += deltaTime * direction * 5.f;
    if (lightComponent.intensity > 5.f || lightComponent.intensity < 0.f)
        direction *= -1.f;

    Cala::Transformation& transformation = entity.getComponent<Coa::TransformComponent>().transformation;
    if (io.isKeyPressed(Cala::IIOSystem::KEY_LEFT))
        transformation.translate(glm::vec3(-deltaTime * 10.f, 0.f, 0.f));

    if (io.isKeyPressed(Cala::IIOSystem::KEY_RIGHT))
        transformation.translate(glm::vec3(deltaTime * 10.f, 0.f, 0.f));

    if (io.isKeyPressed(Cala::IIOSystem::KEY_UP))
        transformation.translate(glm::vec3(0.f, 0.f, -deltaTime * 10.f));

    if (io.isKeyPressed(Cala::IIOSystem::KEY_DOWN))
        transformation.translate(glm::vec3(0.f, 0.f, deltaTime * 10.f));
}