#pragma once
#include "Component.h"
#include "Cala/Rendering/Mesh.h"

namespace Coa {
    struct MeshComponent : public Component {
        enum class Material {
            Plastic,
            Metal,
            Fabric
        };

        MeshComponent() = default;
        MeshComponent(const Cala::Model& model, bool _lightened = true, Material _material = Material::Plastic);
        ~MeshComponent() override = default;
        MeshComponent(const MeshComponent&) = delete;
        MeshComponent(MeshComponent&& other) noexcept;
        MeshComponent& operator=(const MeshComponent&) = delete;
        MeshComponent& operator=(MeshComponent&& other) noexcept;
        const std::string& getModelPath() const { return modelPath; }
        const std::string& getModelName() const { return modelName; }
        void load(const Cala::Model& model, bool _lightened = true, Material _material = Material::Plastic);

        Cala::Mesh mesh;
        bool lightened{ true };
        Material material;

    private:
        std::string modelPath;
        std::string modelName;
    };
}
