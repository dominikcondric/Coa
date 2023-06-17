#include "ScriptComponent.h"

#include "Cala/Utility/Platform.h"
#ifdef CALA_PLATFORM_WINDOWS
    #include <windows.h>
#endif

namespace Coa {
    ScriptComponent::ScriptComponent(const SharedLibrary &library, const std::string& _className)
    {
        loadScript(library, _className);
    }

    ScriptComponent::ScriptComponent(ScriptComponent &&other) noexcept
    {
        *this = std::move(other);
    }

    ScriptComponent &ScriptComponent::operator=(ScriptComponent &&other) noexcept
    {
        script = other.script;
        other.script = nullptr;
        sharedLibrary = std::move(other.sharedLibrary);
        shouldLoadNewEntities = other.shouldLoadNewEntities;
        className = other.className;
        return *this;
    }

    void ScriptComponent::loadScript(const SharedLibrary &library, const std::string& _className)
    {
        className = _className;
        sharedLibrary = library;
        std::string functionName = "load" + className;
        auto scriptFactoryFunction = sharedLibrary.loadFunction<Script*>(functionName.c_str());
        script = scriptFactoryFunction();
    }
}