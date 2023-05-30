#pragma once
#include "Component.h"
#include "Cala/Rendering/Texture.h"

namespace Coa {
    struct SkyboxComponent : public Component {
        SkyboxComponent() = default;
        SkyboxComponent(const std::array<Cala::Image, 6> &images) 
            : texture(images, { Cala::ITexture::WrappingMethod::ClampToEdge, Cala::ITexture::WrappingMethod::ClampToEdge, Cala::ITexture::WrappingMethod::ClampToEdge })
        {
        }

        SkyboxComponent(const SkyboxComponent &) = delete;
        SkyboxComponent(SkyboxComponent &&) noexcept = default;
        SkyboxComponent &operator=(SkyboxComponent &&) noexcept = default;
        SkyboxComponent &operator=(const SkyboxComponent &) = delete;
        ~SkyboxComponent() override = default;
        int blurLevel = 200;
        Cala::Texture texture;
        bool active = true;
    };
}