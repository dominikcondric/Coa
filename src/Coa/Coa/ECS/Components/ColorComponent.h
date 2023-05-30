#pragma once
#include "Component.h"
#include <glm/vec4.hpp>

namespace Coa {
    struct ColorComponent : public Component {
        ColorComponent(const glm::vec4& _color) : color(_color) {}
        glm::vec4 color;
    };
}