# Coa
Project on the way to becoming a game engine.

---

## Building instructions
### Requirements:
* C++17 toolchain
* Modern CMake (version 3.0.0 or higher)
* Coas submodules requirements


### Cloning:
Coa is using git submodules so first recursively clone the repository, and than recursively update all submodules:

```
git clone --recurse-submodules https://github.com/dominikcondric/Coa.git
git submodule update --init --recursive
```

### Building:
Coa is using CMake to simplify development of Coa using different build systems. To generate project files it is advised to create a new directory to where cmake will generate project files:
```
mkdir build
cd build
cmake ..
```

In case you don't want to build demo, set *BUILD_COA_DEMO* option to *OFF*.

*\* If you want to use different build system than the one chosen by CMake, use -G flag with build system in quotes (You can find the list of supported build systems using cmake --help).*