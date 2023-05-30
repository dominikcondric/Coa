#pragma once
#include "Component.h"
#include <glm/vec3.hpp>

namespace Coa {
    struct LightComponent : public Component {
        enum class Type
        {
            Point = 0,
            Directional = 1,
            Spotlight = 2
        };

        LightComponent() = default;
        
        LightComponent(Type _type, float _intensity, const glm::vec3 &_color, float _spotlightCutoff, bool _shadowCaster)
            : type(_type), intensity(_intensity), color(_color), spotlightCutoff(_spotlightCutoff), shadowCaster(_shadowCaster) {}

        ~LightComponent() override = default;

        Type type = Type::Point;
        float intensity = 1.f;
        glm::vec3 color{1.f};
        float spotlightCutoff = 20.f;
        bool shadowCaster = true;
    };
}