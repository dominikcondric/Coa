option(BUILD_COA_DEMO "Quick Coa start guide" ON)

if (${BUILD_COA_DEMO})
    add_executable(CoaDemo
        DemoApplication.h
        DemoApplication.cpp
        main.cpp
    )

    target_compile_definitions(CoaDemo
        PRIVATE
            OUTPUT_DIR="${CMAKE_CURRENT_BINARY_DIR}"
    )

    target_link_libraries(CoaDemo
        PRIVATE
            Coa
    )

    add_library(CoaDemoScripts
        SHARED
            Scripts/MainLightScript.h
            Scripts/MainLightScript.cpp
            Scripts/CameraMovementScript.h
            Scripts/CameraMovementScript.cpp
    )

    target_compile_definitions(CoaDemoScripts
        PRIVATE
            COA_BUILD_DLL
    )

    target_link_libraries(CoaDemoScripts
        PRIVATE
            Coa
    )
endif()