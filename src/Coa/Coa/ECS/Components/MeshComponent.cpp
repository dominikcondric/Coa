#include "MeshComponent.h"

namespace Coa {
    MeshComponent::MeshComponent(const Cala::Model& model, bool _lightened, Material _material) 
        : mesh(model), lightened(_lightened), material(_material), modelPath(model.getModelPath())
    {
    }

    MeshComponent::MeshComponent(MeshComponent &&other) noexcept
        : mesh(std::move(other.mesh)), lightened(other.lightened), material(other.material)
    {
        if (!modelPath.empty())
            modelPath = std::move(other.modelPath);
    }

    MeshComponent &MeshComponent::operator=(MeshComponent&& other) noexcept
    {
        mesh = std::move(other.mesh);
        lightened = other.lightened;
        material = other.material;
        if (!modelPath.empty())
            modelPath = std::move(other.modelPath);
        return *this;
    }
}