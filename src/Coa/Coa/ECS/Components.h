#pragma once
#include <string>
#include "Cala/Rendering/Mesh.h"
#include "Cala/Rendering/Texture.h"
#include <glm/gtc/quaternion.hpp>
#include "Cala/Rendering/Renderers/LightRenderer.h"
#include "Cala/Utility/Transformation.h"
#include "Cala/Rendering/Camera.h"
#include "TypeAliases.h"
#include "Cala/Utility/Image.h"

namespace Coa {
	template<typename T>
	struct ComponentEntity {
		template<typename ...Args>
		ComponentEntity(EntityID ent, Args&&... args) 
			: component(std::forward<Args>(args)...) { entities.push_back(ent); }

		ComponentEntity(const ComponentEntity&) = delete;
		ComponentEntity(ComponentEntity&& other) noexcept :
			entities(std::move(other.entities)), component(std::move(other.component)) 
		{
			// Empty constructor body
		}

		ComponentEntity& operator=(const ComponentEntity&) = delete;
		ComponentEntity& operator=(ComponentEntity&& other) noexcept
		{
			entities = std::move(other.entities);
			component = std::move(other.component);
			return *this;
		}

		~ComponentEntity() = default;

		T component;
		std::vector<EntityID> entities;
	};

	struct Component {
		Component() = default;
		virtual ~Component() = 0;
	};

	struct TagComponent : public Component {
		TagComponent(const std::string& tagName = "") : name(tagName) {}
		~TagComponent() override = default;
		std::string name;
	};

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

		Cala::Mesh mesh;
		std::string_view modelPath;
		bool lightened{ true };
		Material material;
	};

	struct ColorComponent : public Component {
		ColorComponent(const glm::vec4& _color) : color(_color) {}
		glm::vec4 color;
	};

	struct TextureComponent : public Component {
	public:
		TextureComponent() = default;
		TextureComponent(const Cala::Image& diffuseMapImage, const Cala::ITexture::RenderingStyle& textureRenderingStyle = Cala::ITexture::RenderingStyle());
		TextureComponent(const TextureComponent&) = delete;
		TextureComponent(TextureComponent&& other) noexcept = default;
		TextureComponent& operator=(const TextureComponent&) = delete;
		TextureComponent& operator=(TextureComponent&& other) noexcept = default;
		~TextureComponent() override = default;

		Cala::Texture diffuseMap;
		std::string_view diffuseMapPath;

		Cala::Texture specularMap;
		std::string_view specularMapPath;

		Cala::Texture normalMap;
		std::string_view normalMapPath;
	};

	struct CameraComponent : public Component {
		CameraComponent(Cala::Camera::Type cameraType);
		CameraComponent(CameraComponent&&) noexcept = default;
		CameraComponent& operator=(CameraComponent&&) noexcept = default;
		~CameraComponent() override = default;

		Cala::Camera camera;
		bool isMain = true;
	};

	struct LightComponent : public Component {
		enum class Type {
			Point = 0, 
			Directional = 1,
			Spotlight = 2
		};

		LightComponent() = default;
		LightComponent(Type _type, float _intensity, const glm::vec3& _color, float _spotlightCutoff, bool _shadowCaster);
		~LightComponent() override = default;

		Type type = Type::Point;
		float intensity = 1.f;
		glm::vec3 color{ 1.f };
		float spotlightCutoff = 20.f;
		bool shadowCaster = true;
	};

	struct TransformComponent : public Component {
		Cala::Transformation transformation;
	};

	struct SkyboxComponent : public Component {
		SkyboxComponent() = default;
		SkyboxComponent(const std::array<Cala::Image, 6> &images);
		SkyboxComponent(const SkyboxComponent&) = delete;
		SkyboxComponent(SkyboxComponent&&) noexcept = default;
		SkyboxComponent& operator=(SkyboxComponent&&) noexcept = default;
		SkyboxComponent& operator=(const SkyboxComponent&) = delete;
		~SkyboxComponent() override = default;
		int blurLevel = 200;
		Cala::Texture texture;
		bool active = true;
	};
}

