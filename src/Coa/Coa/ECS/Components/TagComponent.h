#pragma once
#include "Component.h"
#include <string>

namespace Coa {
    struct TagComponent : public Component {
        TagComponent(const std::string& tagName = "") : name(tagName) {}
        ~TagComponent() override = default;
        std::string name;
    };
}