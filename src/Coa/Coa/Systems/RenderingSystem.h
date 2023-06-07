#pragma once
#include "Cala/Rendering/Renderers/LightRenderer.h"
#include "Cala/Rendering/Renderers/SimpleRenderer.h"
#include "Cala/Rendering/Renderers/SkyboxRenderer.h"
#include "Cala/Rendering/Renderers/HelperGridRenderer.h"
#include "Coa/ECS/Components/MeshComponent.h"
#include "ISystem.h"
#include "Coa/ECS/Entity.h"

namespace Coa {
    class RenderingSystem : public ISystem {
    public:
        RenderingSystem(Cala::GraphicsAPI* const _api, Cala::Framebuffer* _renderingTarget = nullptr);
        ~RenderingSystem() override = default;
        void run(Scene& scene) override;
        bool renderHelperGrid = false;
        Cala::LightRenderer& getLightRenderer() { return lightRenderer; }
        Cala::SimpleRenderer& getSimpleRenderer() { return simpleRenderer; }
        Cala::HelperGridRenderer& getHelperGridRenderer() { return helperGridRenderer; }
        Cala::SkyboxRenderer& getSkyboxRenderer() { return skyboxRenderer; }

    private:
        struct MaterialCoefficients {
            float ambient;
            float diffuse;
            float specular;
            float shininess;
        };

        MaterialCoefficients generateMaterialCoefficents(Coa::MeshComponent::Material material);
        Cala::Transformation getSceneGraphTransformation(Entity entity) const;

    private:
        Cala::GraphicsAPI* const api;
        Cala::HelperGridRenderer helperGridRenderer;
        Cala::LightRenderer lightRenderer;
        Cala::SimpleRenderer simpleRenderer;
        Cala::SkyboxRenderer skyboxRenderer;
        Cala::Framebuffer* renderingTarget;
        uint32_t celShadingLevelsCount = 0;
    };
}