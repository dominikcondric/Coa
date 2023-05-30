#include "CameraMovementScript.h"
#include "Coa/ECS/Components/CameraComponent.h"
#include <iostream>

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
}