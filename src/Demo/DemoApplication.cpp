#include "DemoApplication.h"
#include "Coa/ECS/Entity.h"
#include "Coa/Systems/RenderingSystem.h"
#include <glm/gtc/random.hpp>
#include "Cala/Utility/Logger.h"
#include <iostream>

DemoApplication::DemoApplication() : 
    window(Cala::Window::construct(Cala::Window::Specification("CoaDemo", 1024, 768, 4))),
    api(Cala::GraphicsAPI::construct())
{
    api->setBufferClearingColor(glm::vec4(0.1f, 0.1f, 0.1f, 1.f));
    api->setBufferClearingBits(true, true, true);
}

DemoApplication::~DemoApplication()
{
}

void DemoApplication::run()
{
    setInitialScene();
    auto winSize = window->getWindowSize();
    api->setViewport(glm::ivec4(0, 0, winSize.x, winSize.y));
    while (!window->exitTriggered())
    {
        loop();
        window->update();
        time.update();
        if (window->isResized())
		{
			auto winSize = window->getWindowSize();
			api->setViewport(glm::uvec4(0, 0, winSize.x, winSize.y));
            for (EntityID e : scene.getComponentEntityList<CameraComponent>())
            {
                CameraComponent& cameraComp = scene.getComponent<CameraComponent>(e);
                if (cameraComp.isMain)
                {
                    cameraComp.camera.setProjectionAspectRatio((float)winSize.x / winSize.y);
                    break;
                }
            }
		}

        Cala::Camera& cam = scene.getComponent<CameraComponent>(scene.getComponentEntityList<CameraComponent>()[0]).camera;
        if (window->getIO().isMouseButtonPressed(Cala::IOSystem::MOUSE_BUTTON_RIGHT))
            cam.rotate(window->getIO().getCursorOffset());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_W))
            cam.move(Cala::Camera::Directions::FORWARD, time.getDeltaTime());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_S))
            cam.move(Cala::Camera::Directions::BACKWARD, time.getDeltaTime());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_A))
            cam.move(Cala::Camera::Directions::LEFT, time.getDeltaTime());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_D))
            cam.move(Cala::Camera::Directions::RIGHT, time.getDeltaTime());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_LEFT_SHIFT))
            cam.move(Cala::Camera::Directions::DOWN, time.getDeltaTime());

        if (window->getIO().isKeyPressed(Cala::IOSystem::KEY_SPACE))
            cam.move(Cala::Camera::Directions::UP, time.getDeltaTime());
    }
}

void DemoApplication::loop()
{
    api->activateFramebuffer(nullptr);
    api->clearFramebuffer();

    engine.run(scene);
}

void DemoApplication::setInitialScene()
{
    Entity cameraEntity = scene.addEntity("camera");
    Cala::Camera& cam = cameraEntity.addComponent<CameraComponent>(Cala::Camera::Type::Perspective).camera;
    cam.setProjectionAspectRatio(1024.f / 768.f);
    cam.setProjectionNearPlane(1.f);
    cam.setProjectionFarPlane(100.f);
    cam.setProjectionViewingAngle(45.f);
    cam.setPosition(glm::vec3(0.f, 20.f, 20.f));

    Entity lightEntity = scene.addEntity("light");
    lightEntity.addComponent<LightComponent>();
    MeshComponent& meshComponent = lightEntity.addComponent<MeshComponent>(Cala::Model().loadSphere(5, 10), false);
    lightEntity.getComponent<TransformComponent>().transformation.translate(glm::vec3(0.f, 4.f, 0.f)).scale(0.2f);

    Entity sphereEntity = scene.addEntity("first sphere");
    sphereEntity.addComponent<MeshComponent>(Cala::Model().loadSphere());

    for (int i = 0; i < 30; ++i)
    {
        Entity e = scene.addEntity();
        e.shareComponent<MeshComponent>(sphereEntity);
        e.addComponent<ColorComponent>(glm::vec4(glm::abs(glm::ballRand(1.f)), 1.f));
        Cala::Transformation& t = e.getComponent<TransformComponent>().transformation;
        t.translate(glm::ballRand(20.f)).scale(glm::linearRand(0.5f, 2.f));
    }

    RenderingSystem* renderingSystem = new RenderingSystem(api.get());
    renderingSystem->setShadows(false);
    engine.addSystem(renderingSystem);
}
