#pragma once
#include "Component.h"
#include <string>

namespace Coa {
    struct TagComponent : public Component {
        TagComponent(const std::string& tagName = "") : name(tagName) {}
        TagComponent(const TagComponent& other) = default;
        TagComponent& operator=(const TagComponent& other) = default;
        TagComponent(TagComponent&& other) noexcept = default;
        TagComponent& operator=(TagComponent&& other) noexcept = default;
        ~TagComponent() override = default;
        std::string name;
    };
}