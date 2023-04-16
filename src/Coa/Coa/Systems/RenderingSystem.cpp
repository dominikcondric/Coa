#include "RenderingSystem.h"
#include "Cala/Utility/Logger.h"

namespace Coa {
    RenderingSystem::RenderingSystem(Cala::GraphicsAPI *const _api, Cala::Framebuffer* _renderingTarget) 
        : api(_api), skyboxRenderer(nullptr), renderingTarget(_renderingTarget)
    {
    }

    void RenderingSystem::run(Scene &scene)
    {
        for (const EntityID e : scene.getComponentEntityList<CameraComponent>())
        {
            const CameraComponent& cameraComp = scene.getComponent<CameraComponent>(e);
            if (cameraComp.isMain)
            {
                simpleRenderer.setupCamera(cameraComp.camera);
                lightRenderer.setupCamera(cameraComp.camera);
                skyboxRenderer.setupCamera(cameraComp.camera);
                break;
            }
        }

        for (const EntityID e : scene.getComponentEntityList<LightComponent>())
        {
            const LightComponent& lightComp = scene.getComponent<LightComponent>(e);
            const TransformComponent& transformComp = scene.getComponent<TransformComponent>(e);

            lightRenderer.pushLight(Cala::LightRenderer::Light(
                (Cala::LightRenderer::Light::Type)lightComp.type, transformComp.transformation, lightComp.intensity, lightComp.color,
                lightComp.spotlightCutoff, lightComp.shadowCaster
            ));
        }

        for (const EntityID e : scene.getComponentEntityList<SkyboxComponent>())
        {
            SkyboxComponent& skyboxComp = scene.getComponent<SkyboxComponent>(e);
            const TransformComponent& transformComp = scene.getComponent<TransformComponent>(e);

            if (skyboxComp.active)
            {
                skyboxRenderer.setTexture(&skyboxComp.texture);
                break;
            }
        }


        for (const EntityID e : scene.getComponentEntityList<MeshComponent>())
        {
            const MeshComponent& renderingComp = scene.getComponent<MeshComponent>(e);
            const TransformComponent& transformComp = scene.getComponent<TransformComponent>(e);
            glm::vec4 color(1.f);
            if (scene.hasComponent<ColorComponent>(e))
                color = scene.getComponent<ColorComponent>(e).color;
            Cala::Texture* diffuseMap = nullptr;
            if (scene.hasComponent<TextureComponent>(e))
            {
                TextureComponent& texComp = scene.getComponent<TextureComponent>(e);
                diffuseMap = &texComp.diffuseMap;
            }
            

            if (renderingComp.lightened)
            {
                lightRenderer.pushRenderable(Cala::LightRenderer::Renderable(
                    renderingComp.mesh, transformComp.transformation, color,
                    diffuseMap, nullptr, nullptr, 0.1f, 0.9f, 0.8f, 30.f
                ));
            }
            else
            {
                simpleRenderer.pushRenderable(Cala::SimpleRenderer::Renderable(
                    renderingComp.mesh, transformComp.transformation, color
                ));
            }
        }

        simpleRenderer.render(api, renderingTarget);
        lightRenderer.render(api, renderingTarget);
        skyboxRenderer.render(api, renderingTarget);
    }
}