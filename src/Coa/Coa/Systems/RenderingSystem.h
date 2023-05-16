#pragma once
#include "Cala/Rendering/Renderers/LightRenderer.h"
#include "Cala/Rendering/Renderers/SimpleRenderer.h"
#include "Cala/Rendering/Renderers/SkyboxRenderer.h"
#include "ISystem.h"
#include "Coa/ECS/Entity.h"

namespace Coa {
    class RenderingSystem : public ISystem {
    public:
        RenderingSystem(Cala::GraphicsAPI* const _api, Cala::Framebuffer* _renderingTarget = nullptr);
        ~RenderingSystem() override = default;
        void run(Scene& scene) override;
        void setShadows(bool shadows);
        void enableCelShading(uint32_t levelCount) { lightRenderer.enableCelShading(levelCount); }
        void disableCelShading() { lightRenderer.disableCelShading(); }

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
        Cala::LightRenderer lightRenderer;
        Cala::SimpleRenderer simpleRenderer;
        Cala::SkyboxRenderer skyboxRenderer;
        Cala::Framebuffer* renderingTarget;
    };
}