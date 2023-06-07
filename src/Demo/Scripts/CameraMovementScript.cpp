#include "CameraMovementScript.h"
#include "Coa/ECS/Components/CameraComponent.h"
#include "Coa/ECS/Components/MeshComponent.h"
#include "Coa/ECS/Components/ColorComponent.h"
#include "Coa/ECS/Components/TransformComponent.h"
#include <glm/gtc/random.hpp>

void CameraMovementScript::execute(Coa::Entity entity, const Cala::IIOSystem &io, float deltaTime)
{
    Cala::Camera& camera = entity.getComponent<Coa::CameraComponent>().camera;
    if (io.isMouseButtonPressed(Cala::IIOSystem::MOUSE_BUTTON_RIGHT))
        camera.rotate(io.getCursorOffset());

    if (io.isKeyPressed(Cala::IIOSystem::KEY_W))
        camera.move(Cala::Camera::Directions::FORWARD, deltaTime);

    if (io.isKeyPressed(Cala::IIOSystem::KEY_S))
        camera.move(Cala::Camera::Directions::BACKWARD, deltaTime);

    if (io.isKeyPressed(Cala::IIOSystem::KEY_A))
        camera.move(Cala::Camera::Directions::LEFT, deltaTime);

    if (io.isKeyPressed(Cala::IIOSystem::KEY_D))
        camera.move(Cala::Camera::Directions::RIGHT, deltaTime);

    if (io.isKeyPressed(Cala::IIOSystem::KEY_LEFT_SHIFT))
        camera.move(Cala::Camera::Directions::DOWN, deltaTime);

    if (io.isKeyPressed(Cala::IIOSystem::KEY_SPACE))
        camera.move(Cala::Camera::Directions::UP, deltaTime);

    if (io.isKeyTapped(Cala::IIOSystem::KEY_ENTER))
        entity.getComponent<Coa::ScriptComponent>().shouldLoadNewEntities = true;
}

void CameraMovementScript::loadNewEntities(Coa::Scene &scene)
{
    Coa::Entity cubeEntity = scene.addEntity("cube"); 
    cubeEntity.addComponent<Coa::MeshComponent>(Cala::Model().loadCube()).mesh.cullingEnabled = true;
    cubeEntity.addComponent<Coa::ColorComponent>(glm::vec4(glm::abs(glm::ballRand<float>(1.f)), 1.f));
    cubeEntity.getComponent<Coa::TransformComponent>().transformation.translate(glm::ballRand<float>(10.f));

    Coa::Entity satelliteCubeEntity = scene.addEntity("satellite", cubeEntity.getEntityID());
    Coa::MeshComponent& meshComp = satelliteCubeEntity.addComponent<Coa::MeshComponent>(Cala::Model().loadCube());
    satelliteCubeEntity.addComponent<Coa::ColorComponent>(glm::vec4(glm::abs(glm::ballRand<float>(1.f)), 1.f));
    satelliteCubeEntity.getComponent<Coa::TransformComponent>().transformation.translate(glm::ballRand<float>(2.f)).scale(0.2f);
}
