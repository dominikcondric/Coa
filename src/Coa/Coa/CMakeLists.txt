set(coa_src_files 
    ECS/ComponentDatabase.h
    ECS/Components.cpp
    ECS/Components.h
    ECS/ConsistentComponentVector.h
    ECS/Entity.h 
    ECS/Entity.cpp
    ECS/Scene.cpp
    ECS/Scene.h
    
    Utility/IterableVector.h
    Utility/ConsistentVector.h

    Systems/ISystem.h Systems/ISystem.cpp
    Systems/RenderingSystem.h Systems/RenderingSystem.cpp
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