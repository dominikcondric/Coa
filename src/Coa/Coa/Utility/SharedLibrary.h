#pragma once
#include "Cala/Utility/Platform.h"
#include <filesystem>
#include <unordered_map>

#ifdef CALA_PLATFORM_WINDOWS
    #include <windows.h>
#endif

namespace Coa {
    template<typename ReturnType, typename ...Args>
    using FunctionPointer = ReturnType (*)(Args...);

    class SharedLibrary {
    public:
        SharedLibrary() = default;
        SharedLibrary(const std::filesystem::path& libraryPath);
        SharedLibrary(const SharedLibrary& other);
        SharedLibrary(SharedLibrary&& other) noexcept;
        SharedLibrary& operator=(const SharedLibrary& other);
        SharedLibrary& operator=(SharedLibrary&& other) noexcept;
        ~SharedLibrary();
        void load(const std::filesystem::path& libraryPath);
        void free();
        const std::string& getPath() const { return path; }

        template<typename ReturnType, typename ...Args>
        FunctionPointer<ReturnType, Args...> loadFunction(std::string_view functionName) const
        {
            if (libraryHandle == nullptr)
                return nullptr;

            using FunctionPointerType = FunctionPointer<ReturnType, Args...>;
            auto address = GetProcAddress((HMODULE)libraryHandle, functionName.data());
            return reinterpret_cast<FunctionPointerType>(address);
        }

    private:
        void* libraryHandle = nullptr;
        std::string path;
        static std::unordered_map<std::string, std::pair<void*, uint32_t>> openHandles;
    };
}