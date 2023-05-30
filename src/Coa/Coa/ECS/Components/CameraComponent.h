#pragma once
#include "Component.h"
#include "Cala/Rendering/Camera.h"

namespace Coa {
    struct CameraComponent : public Component {
        CameraComponent(Cala::Camera::Type cameraType) : camera(cameraType) {}
        CameraComponent(CameraComponent &&) noexcept = default;
        CameraComponent &operator=(CameraComponent &&) noexcept = default;
        ~CameraComponent() override = default;

        Cala::Camera camera;
        bool isMain = true;
    };
}