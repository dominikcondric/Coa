#include "DemoApplication.h"
#include "Coa/ECS/Entity.h"
#include "Coa/Systems/RenderingSystem.h"
#include "Cala/Utility/Logger.h"
#include "Coa/ECS/Components/CameraComponent.h"
#include "Coa/ECS/Components/LightComponent.h"
#include "Coa/ECS/Components/MeshComponent.h"
#include "Coa/ECS/Components/ColorComponent.h"
#include "Coa/ECS/Components/TransformComponent.h"
#include "Coa/ECS/Components/ScriptComponent.h"
#include "Cala/Utility/GLFWWindow.h"
#include <glm/gtc/random.hpp>

DemoApplication::DemoApplication() : 
    window(new Cala::GLFWWindow(Cala::IWindow::Specification("CoaDemo", 1024, 768, 4))),
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
        window->update();
        time.update();
        loop();

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
    }
}

void DemoApplication::loop()
{
    api->activateFramebuffer(nullptr);
    api->clearFramebuffer();

    scriptingSystem->setDeltaTime(time.getDeltaTime());
    engine.run(scene);
}

void DemoApplication::setInitialScene()
{
    SharedLibrary sharedLibrary(std::filesystem::path(OUTPUT_DIR) / "libCoaDemoScripts.dll");

    Entity cameraEntity = scene.addEntity("camera");
    Cala::Camera& cam = cameraEntity.addComponent<CameraComponent>(Cala::Camera::Type::Perspective).camera;
    cam.setProjectionAspectRatio(1024.f / 768.f);
    cam.setProjectionNearPlane(1.f);
    cam.setProjectionFarPlane(100.f);
    cam.setProjectionViewingAngle(45.f);
    cam.setPosition(glm::vec3(0.f, 20.f, 20.f));
    cameraEntity.addComponent<ScriptComponent>(sharedLibrary, "CameraMovementScript");

    Entity lightEntity = scene.addEntity("light");
    lightEntity.addComponent<LightComponent>();
    MeshComponent& meshComponent = lightEntity.addComponent<MeshComponent>(Cala::Model().loadSphere(5, 10), false);
    meshComponent.mesh.cullingEnabled = true;
    lightEntity.getComponent<TransformComponent>().transformation.translate(glm::vec3(0.f, 4.f, 0.f)).scale(0.2f);
    lightEntity.addComponent<ScriptComponent>().loadScript(sharedLibrary, "MainLightScript");

    Entity sphereEntity = scene.addEntity("First sphere");
    sphereEntity.addComponent<MeshComponent>(Cala::Model().loadSphere()).mesh.cullingEnabled = true;
    sphereEntity.getComponent<TransformComponent>().transformation.translate(glm::vec3(10.f, 10.f, 0.f));

    for (int i = 0; i < 30; ++i)
    {
        Entity e = scene.addEntity("", sphereEntity.getEntityID());
        e.shareComponent<MeshComponent>(sphereEntity);
        e.addComponent<ColorComponent>(glm::vec4(glm::abs(glm::ballRand(1.f)), 1.f));
        Cala::Transformation& t = e.getComponent<TransformComponent>().transformation;
        t.translate(glm::ballRand(20.f)).scale(glm::linearRand(0.5f, 2.f));
    }

    renderingSystem.reset(new RenderingSystem(api.get()));
    renderingSystem->getHelperGridRenderer().gridColor = glm::vec4(.9f, .7f, .2f, 1.f);
    engine.addSystem(renderingSystem.get());

    scriptingSystem.reset(new ScriptingSystem(window->getIO()));
    engine.addSystem(scriptingSystem.get());

    sceneManagementSystem.reset(new SceneManagementSystem());
    engine.addSystem(sceneManagementSystem.get());
}
