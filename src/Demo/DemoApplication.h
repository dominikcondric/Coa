#pragma once
#include "Cala/Utility/BaseApplication.h"
#include "Coa/Systems/Engine.h"
#include "Coa/ECS/Scene.h"
#include "Cala/Utility/Window.h"
#include "Cala/Rendering/GraphicsAPI.h"
#include "Cala/Rendering/Renderers/SimpleRenderer.h"

using namespace Coa; 

class DemoApplication {
public:
    DemoApplication();
    ~DemoApplication();
    void run();

private:
    std::unique_ptr<Cala::Window> window;
    std::unique_ptr<Cala::GraphicsAPI> api;
    Engine engine;
    Scene scene;
    Cala::SimpleRenderer simpleRenderer;
    Cala::Time time;

    void setInitialScene();
    void loop();
};