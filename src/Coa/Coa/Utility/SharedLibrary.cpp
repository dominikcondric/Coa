#include "SharedLibrary.h"

namespace Coa {
    SharedLibrary::~SharedLibrary()
    {
        free();
    }

    void SharedLibrary::load(const std::filesystem::path &libraryPath)
    {
        if (!std::filesystem::exists(libraryPath))
            return;

    #ifdef CALA_PLATFORM_WINDOWS
        if (libraryPath.extension() != ".dll")
            return;

        path = libraryPath.string();
        libraryHandle = LoadLibrary(libraryPath.generic_string().c_str());

    #endif
    }

    void SharedLibrary::free()
    {
        #ifdef CALA_PLATFORM_WINDOWS
        if (libraryHandle == nullptr)
            return;
        
        FreeLibrary((HMODULE)libraryHandle);
    #endif
    }
}
