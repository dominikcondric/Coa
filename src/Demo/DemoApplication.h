#pragma once
#include "Coa/Systems/Engine.h"
#include "Coa/ECS/Scene.h"
#include "Cala/Utility/IWindow.h"
#include "Coa/Utility/SharedLibrary.h"
#include "Cala/Rendering/GraphicsAPI.h"
#include "Coa/Systems/RenderingSystem.h"
#include "Coa/Systems/ScriptingSystem.h"
#include "Coa/Systems/SceneManagementSystem.h"
#include "Cala/Utility/Time.h"

using namespace Coa; 

class DemoApplication {
public:
    DemoApplication();
    ~DemoApplication();
    void run();

private:
    std::unique_ptr<Cala::IWindow> window;
    std::unique_ptr<Cala::GraphicsAPI> api;
    Engine engine;
    Scene scene;
    Cala::Time time;
    std::unique_ptr<RenderingSystem> renderingSystem;
    std::unique_ptr<ScriptingSystem> scriptingSystem;
    std::unique_ptr<SceneManagementSystem> sceneManagementSystem;

    void setInitialScene();
    void loop();
};