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
        return *this;
    }

    void ScriptComponent::loadScript(const SharedLibrary &library, const std::string& _className)
    {
        className = _className;
        sharedLibraryPath = library.getPath();
        std::string functionName = "load" + className;
        auto scriptFactoryFunction = library.loadFunction<Script*>(functionName.c_str());
        script = scriptFactoryFunction();
    }
}