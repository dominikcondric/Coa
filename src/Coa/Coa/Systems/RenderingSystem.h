#pragma once
#include "Cala/Rendering/Renderers/LightRenderer.h"
#include "Cala/Rendering/Renderers/SimpleRenderer.h"
#include "Cala/Rendering/Renderers/SkyboxRenderer.h"
#include "ISystem.h"

namespace Coa {
    class RenderingSystem : public ISystem {
    public:
        RenderingSystem(Cala::GraphicsAPI* const _api, Cala::Framebuffer* _renderingTarget = nullptr);
        ~RenderingSystem() override = default;
        void run(Scene& scene) override;

    private:
        Cala::GraphicsAPI* const api;
        Cala::LightRenderer lightRenderer;
        Cala::SimpleRenderer simpleRenderer;
        Cala::SkyboxRenderer skyboxRenderer;
        Cala::Framebuffer* renderingTarget;
    };
}