#include "Components.h"

namespace Coa {
	Component::~Component()
	{
		// Empty destructor body
	}

    MeshComponent::MeshComponent(const Cala::Model& model, bool _lightened, Material _material) 
		: mesh(model), lightened(_lightened), material(_material), modelPath(model.getModelPath())
    {
    }

	MeshComponent::MeshComponent(MeshComponent &&other) noexcept
		: mesh(std::move(other.mesh)), lightened(other.lightened), material(other.material), 
		modelPath(std::move(modelPath))
	{
	}

	MeshComponent &MeshComponent::operator=(MeshComponent&& other) noexcept
	{
		mesh = std::move(other.mesh);
		lightened = other.lightened;
		material = other.material;
		modelPath = std::move(modelPath);
		return *this;
	}

	LightComponent::LightComponent(Type _type, float _intensity, const glm::vec3 &_color, float _spotlightCutoff, bool _shadowCaster)
		: type(_type), intensity(_intensity), color(_color), spotlightCutoff(_spotlightCutoff), shadowCaster(_shadowCaster)
	{
	}

	CameraComponent::CameraComponent(Cala::Camera::Type cameraType) : camera(cameraType)
	{
	}

    TextureComponent::TextureComponent(const Cala::Image& diffuseMapImage, const Cala::ITexture::RenderingStyle& textureRenderingStyle) 
		: diffuseMap(diffuseMapImage, textureRenderingStyle), diffuseMapPath(diffuseMapImage.getPath())
    {
    }

    SkyboxComponent::SkyboxComponent(const std::array<Cala::Image, 6> &images) 
		: texture(images, { Cala::ITexture::WrappingMethod::ClampToEdge, Cala::ITexture::WrappingMethod::ClampToEdge, Cala::ITexture::WrappingMethod::ClampToEdge })
    {
    }
}
