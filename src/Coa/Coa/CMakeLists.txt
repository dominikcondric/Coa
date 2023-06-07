set(coa_src_files 
    ECS/ComponentDatabase.h
    ECS/ConsistentComponentVector.h
    ECS/Entity.h 
    ECS/Entity.cpp
    ECS/Scene.cpp
    ECS/Scene.h

    ECS/Components/Component.h
    ECS/Components/Component.cpp
    ECS/Components/ColorComponent.h
    ECS/Components/TransformComponent.h
    ECS/Components/TextureComponent.h
    ECS/Components/ScriptComponent.h
    ECS/Components/ScriptComponent.cpp
    ECS/Components/MeshComponent.h
    ECS/Components/MeshComponent.cpp
    ECS/Components/LightComponent.h
    ECS/Components/TagComponent.h
    ECS/Components/SkyboxComponent.h
    ECS/Components/DestroyEntityComponent.h
    ECS/Components/CameraComponent.h
    ECS/Components/ComponentEntity.h
    
    Utility/IterableVector.h
    Utility/ConsistentVector.h
    Utility/SharedLibrary.h
    Utility/SharedLibrary.cpp

    Systems/ISystem.h Systems/ISystem.cpp
    Systems/SceneManagementSystem.h Systems/SceneManagementSystem.cpp
    Systems/RenderingSystem.h Systems/RenderingSystem.cpp
    Systems/ScriptingSystem.h Systems/ScriptingSystem.cpp
    Systems/Engine.h Systems/Engine.cpp
)

add_library(Coa
    STATIC
        ${coa_src_files}
)

target_link_libraries(Coa
    PUBLIC
        Cala
)

target_include_directories(Coa
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/../
)