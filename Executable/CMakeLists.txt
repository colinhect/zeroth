project(ZerothExecutable CXX)

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

add_executable(ZerothExecutable ${SOURCE_FILES})

target_link_libraries(ZerothExecutable Zeroth Hect)

set_target_properties(ZerothExecutable PROPERTIES
    PROJECT_LABEL ZerothExecutable
    OUTPUT_NAME PlayZeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )
