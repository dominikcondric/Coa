#include "RenderingSystem.h"
#include "Cala/Utility/Logger.h"
#include "Coa/ECS/Components/CameraComponent.h"
#include "Coa/ECS/Components/LightComponent.h"
#include "Coa/ECS/Components/TextureComponent.h"
#include "Coa/ECS/Components/TransformComponent.h"
#include "Coa/ECS/Components/SkyboxComponent.h"
#include "Coa/ECS/Components/ColorComponent.h"

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
                helperGridRenderer.setupCamera(cameraComp.camera);
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
                (Cala::LightRenderer::Light::Type)lightComp.type, getSceneGraphTransformation(Entity(&scene, e)), lightComp.intensity, lightComp.color,
                lightComp.spotlightCutoff, lightComp.shadowCaster
            ));
        }

        for (const EntityID e : scene.getComponentEntityList<SkyboxComponent>())
        {
            SkyboxComponent& skyboxComp = scene.getComponent<SkyboxComponent>(e);

            if (skyboxComp.active && skyboxComp.texture.isLoaded())
            {
                skyboxRenderer.setTexture(&skyboxComp.texture);
                break;
            }
        }

        for (const EntityID e : scene.getComponentEntityList<MeshComponent>())
        {
            const MeshComponent& renderingComp = scene.getComponent<MeshComponent>(e);
            Cala::Transformation transformation = getSceneGraphTransformation(Entity(&scene, e));
            
            glm::vec4 color(1.f);
            if (scene.hasComponent<ColorComponent>(e))
                color = scene.getComponent<ColorComponent>(e).color;

            Cala::Texture* diffuseMap = nullptr;
            Cala::Texture* specularMap = nullptr;
            Cala::Texture* normalMap = nullptr;

            if (scene.hasComponent<TextureComponent>(e))
            {
                TextureComponent& texComp = scene.getComponent<TextureComponent>(e);
                if (!texComp.diffuseMapPath.empty())
                    diffuseMap = &texComp.diffuseMap;

                if (!texComp.specularMapPath.empty())
                    specularMap = &texComp.specularMap;

                if (!texComp.normalMapPath.empty())
                    normalMap = &texComp.normalMap;
            }

            if (renderingComp.lightened)
            {
                MaterialCoefficients materialCoefficients = generateMaterialCoefficents(renderingComp.material);
                lightRenderer.pushRenderable(Cala::LightRenderer::Renderable(
                    renderingComp.mesh, transformation, color,
                    diffuseMap, nullptr, nullptr, materialCoefficients.ambient,
                    materialCoefficients.diffuse, materialCoefficients.specular, materialCoefficients.shininess
                ));
            }
            else
            {
                simpleRenderer.pushRenderable(Cala::SimpleRenderer::Renderable(
                    renderingComp.mesh, transformation, color
                ));
            }
        }


        if (renderHelperGrid)
            helperGridRenderer.render(api, renderingTarget);
            
        lightRenderer.render(api, renderingTarget);
        simpleRenderer.render(api, renderingTarget);
        skyboxRenderer.render(api, renderingTarget);
    }
    
    RenderingSystem::MaterialCoefficients RenderingSystem::generateMaterialCoefficents(Coa::MeshComponent::Material material)
    {
        MaterialCoefficients coefficients;
        switch (material)
        {
        case Coa::MeshComponent::Material::Plastic:
            coefficients.ambient = 0.f;
            coefficients.diffuse = 0.55f;
            coefficients.specular = 0.7f;
            coefficients.shininess = 40.f;
            break;
        
        case Coa::MeshComponent::Material::Metal:
            coefficients.ambient = 0.1f;
            coefficients.diffuse = 0.6f;
            coefficients.specular = 0.94f;
            coefficients.shininess = 100.f;
            break;

        case Coa::MeshComponent::Material::Fabric:
            coefficients.ambient = 0.f;
            coefficients.diffuse = 0.7f;
            coefficients.specular = 0.4f;
            coefficients.shininess = 5.f;
            break;
        }

        return coefficients;
    }

    Cala::Transformation RenderingSystem::getSceneGraphTransformation(Entity entity) const
    {
        if (entity.getParent().getEntityID() == -1)
            return entity.getComponent<TransformComponent>().transformation;

        Cala::Transformation transformation = entity.getComponent<TransformComponent>().transformation;
        const Cala::Transformation& parentTransform = getSceneGraphTransformation(entity.getParent());
        transformation.translate(parentTransform.getTranslation());
        transformation.scale(parentTransform.getScale());
        transformation.rotate(
            transformation.getRotationQuat().x,
            glm::vec3(transformation.getRotationQuat().y, transformation.getRotationQuat().z, transformation.getRotationQuat().w)
        );

        return transformation;
    }
}