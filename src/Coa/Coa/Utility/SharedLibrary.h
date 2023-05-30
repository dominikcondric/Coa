#pragma once
#include "Cala/Utility/Platform.h"
#include <filesystem>

#ifdef CALA_PLATFORM_WINDOWS
    #include <windows.h>
#endif

template<typename ReturnType, typename ...Args>
using FunctionPointer = ReturnType (*)(Args...);

class SharedLibrary {
public:
    SharedLibrary() = default;
    ~SharedLibrary();
    void load(const std::filesystem::path& libraryPath);
    void free();
    const std::string& getPath() const { return path; }

    template<typename ReturnType, typename ...Args>
    FunctionPointer<ReturnType, Args...> loadFunction(std::string_view functionName) const
    {
        if (libraryHandle == NULL)
            return nullptr;

        using FunctionPointerType = FunctionPointer<ReturnType, Args...>;
        auto address = GetProcAddress((HMODULE)libraryHandle, functionName.data());
        return reinterpret_cast<FunctionPointerType>(address);
    }

private:
    void* libraryHandle = nullptr;
    std::string path;
};