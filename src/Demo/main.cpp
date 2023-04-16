#include "DemoApplication.h"

int main(int argc, char* argv[])
{
    DemoApplication* app = new DemoApplication;
    app->run();
    delete app;
}