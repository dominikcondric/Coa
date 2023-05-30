#pragma once
#include "Component.h"
#include "Cala/Utility/IIOSystem.h"
#include "Coa/Utility/SharedLibrary.h"
#include "Coa/ECS/Entity.h"
#include "Cala/Utility/Platform.h"

#ifdef CALA_PLATFORM_WINDOWS
    #ifdef COA_BUILD_DLL
        #define COA_DLL __declspec(dllexport)
    #else
        #define COA_DLL __declspec(dllimport)
    #endif
#else
    #define COA_DLL
#endif

namespace Coa {
    struct ScriptComponent : public Component {
        class COA_DLL Script {
        public:
            Script() = default;
            virtual ~Script() = default;
            virtual void execute(Entity entity, const Cala::IIOSystem& io, float deltaTime) = 0;
        };
    
        ScriptComponent() = default;
        ScriptComponent(const SharedLibrary& library, const std::string& _className);
        ScriptComponent(ScriptComponent&& other) noexcept;
        ScriptComponent& operator=(ScriptComponent&& other) noexcept;
        ~ScriptComponent() { delete script; }
        void loadScript(const SharedLibrary& library, const std::string& _className);
        void executeScript(Entity entity, const Cala::IIOSystem& io, float deltaTime);

    private:
        Script* script = nullptr;
        std::string sharedLibraryPath;
        std::string className;
    };
}