#pragma once
#include "Component.h"
#include "Cala/Utility/IIOSystem.h"
#include "Coa/Utility/SharedLibrary.h"
#include "Coa/ECS/Entity.h"
#include "Cala/Utility/Platform.h"
#include "Cala/Rendering/GraphicsAPI.h"


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
    class Scene;

    struct ScriptComponent : public Component {
        class COA_DLL Script {
        public:
            Script()
            {
                /*
                 It is necessary to load API functions because
                 outside process that calls the script, 
                 global symbols (such as OpenGL state symbols) are not visible
                */ 
                Cala::GraphicsAPI::loadAPIFunctions();
            }

            virtual ~Script() = default;
            virtual void execute(Entity entity, const Cala::IIOSystem& io, float deltaTime) = 0;
            virtual void loadNewEntities(Scene& scene) { /* Empty definition */ };
        };
    
        ScriptComponent() = default;
        ScriptComponent(const SharedLibrary& library, const std::string& _className);
        ScriptComponent(ScriptComponent&& other) noexcept;
        ScriptComponent& operator=(ScriptComponent&& other) noexcept;
        ~ScriptComponent() { delete script; }
        void loadScript(const SharedLibrary& library, const std::string& _className);
        Script* getScript() const { return script; };
        const std::string& getSharedLibraryPath() const { return sharedLibraryPath; }
        const std::string& getClassName() const { return className; }

    public:
        bool shouldLoadNewEntities = false;

    private:
        Script* script = nullptr;
        std::string sharedLibraryPath;
        std::string className;
    };
}