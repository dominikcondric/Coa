#include "MeshComponent.h"

namespace Coa {
    MeshComponent::MeshComponent(const Cala::Model& model, bool _lightened, Material _material)
    {
        load(model, _lightened, _material);
    }

    MeshComponent::MeshComponent(MeshComponent &&other) noexcept
        : mesh(std::move(other.mesh)), lightened(other.lightened), material(other.material)
    {
        if (!modelPath.empty())
            modelPath = std::move(other.modelPath);

        if (!modelName.empty())
            modelName = std::move(other.modelName);
    }

    MeshComponent &MeshComponent::operator=(MeshComponent&& other) noexcept
    {
        mesh = std::move(other.mesh);
        lightened = other.lightened;
        material = other.material;
        if (!modelPath.empty())
            modelPath = std::move(other.modelPath);

        if (!modelName.empty())
            modelName = std::move(other.modelName);
            
        return *this;
    }

    void MeshComponent::load(const Cala::Model &model, bool _lightened, Material _material)
    {
        mesh.loadFromModel(model, false, false);
        lightened = _lightened;
        material = _material;
        modelName = model.getModelName();
        modelPath = model.getModelPath();
    }
}