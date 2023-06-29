#include "SharedLibrary.h"

namespace Coa {
    std::unordered_map<std::string, std::pair<void*, uint32_t>> SharedLibrary::openHandles;

    SharedLibrary::SharedLibrary(const std::filesystem::path &libraryPath)
    {
        load(libraryPath);
    }

    SharedLibrary::SharedLibrary(const SharedLibrary &other)
    {
        *this = other;
    }

    SharedLibrary::SharedLibrary(SharedLibrary &&other) noexcept
    {
        *this = std::move(other);
    }

    SharedLibrary& SharedLibrary::operator=(const SharedLibrary &other)
    {
        libraryHandle = other.libraryHandle;
        path = other.path;

        if (!path.empty())
            openHandles.at(path).second++;

        return *this;
    }

    SharedLibrary &SharedLibrary::operator=(SharedLibrary &&other) noexcept
    {
        libraryHandle = other.libraryHandle;
        other.libraryHandle = nullptr;
        path = other.path;
        return *this;
    }

    SharedLibrary::~SharedLibrary()
    {
        free();
    }

    void SharedLibrary::load(const std::filesystem::path &libraryPath)
    {
        if (!std::filesystem::exists(libraryPath))
            return;

        path = libraryPath.string();
        if (openHandles.find(libraryPath.string()) != openHandles.end())
        {
            auto entry = openHandles.at(libraryPath.string());
            libraryHandle = entry.first;
            entry.second += 1;
        }
        else
        {
        #ifdef CALA_PLATFORM_WINDOWS
            if (libraryPath.extension() != ".dll")
                return;

            libraryHandle = LoadLibrary(libraryPath.generic_string().c_str());
            openHandles.insert({ path, { libraryHandle, 1 }  });
        #endif
        }
    }

    void SharedLibrary::free()
    {
        if (libraryHandle == nullptr)
            return;

        openHandles.at(path).second -= 1;
        if (openHandles.at(path).second == 0)
        {
        #ifdef CALA_PLATFORM_WINDOWS
            FreeLibrary((HMODULE)libraryHandle);
        #endif

            openHandles.erase(path);
        }
    }
}
