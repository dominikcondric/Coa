#pragma once
#include "Component.h"
#include "Cala/Rendering/Texture.h"

namespace Coa {
    struct TextureComponent : public Component {
	public:
		TextureComponent() = default;
        TextureComponent(const Cala::Image& diffuseMapImage, const Cala::ITexture::RenderingStyle& textureRenderingStyle) 
            : diffuseMap(diffuseMapImage, textureRenderingStyle), diffuseMapPath(diffuseMapImage.getPath()) {}
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&& other) noexcept = default;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = default;
		~TextureComponent() override = default;

		Cala::Texture diffuseMap;
		std::string diffuseMapPath;

		Cala::Texture specularMap;
		std::string specularMapPath;

		Cala::Texture normalMap;
		std::string normalMapPath;
	};
}