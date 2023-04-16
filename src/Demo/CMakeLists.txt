option(BUILD_COA_DEMO "Quick Coa start guide" ON)

if (${BUILD_COA_DEMO})
    add_executable(CoaDemo
        DemoApplication.h
        DemoApplication.cpp
        main.cpp
    )

    target_link_libraries(CoaDemo
        PRIVATE
            Coa
    )
endif()