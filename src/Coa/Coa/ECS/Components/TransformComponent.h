#pragma once
#include "Component.h"
#include "Cala/Utility/Transformation.h"

namespace Coa {
    struct TransformComponent : public Component {
        Cala::Transformation transformation;
    };
}