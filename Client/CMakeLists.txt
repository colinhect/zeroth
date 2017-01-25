project(ZerothClient CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/../Source"
    "${PROJECT_SOURCE_DIR}/../../../Engine/Source"
    )

set(SOURCE_FILES
    "../Source/Main.cpp"
    )

source_group("Source" FILES
    "../Source/Main.cpp"
    )

add_executable(ZerothClient ${SOURCE_FILES})

target_link_libraries(ZerothClient Zeroth Hect)

set_target_properties(ZerothClient PROPERTIES
    PROJECT_LABEL ZerothClient
    OUTPUT_NAME ZerothClient
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )
