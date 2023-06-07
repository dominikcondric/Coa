#pragma once
#include "Component.h"

namespace Coa {
    struct DestroyEntityComponent : public Component {
        bool destroy = false;
    };
}