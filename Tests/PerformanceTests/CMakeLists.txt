project(ZerothPerformanceTests CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Werror -pedantic")
endif()

add_definitions(-DCELERO_STATIC)

include_directories(
    "${PROJECT_SOURCE_DIR}/../../Source"
    "${PROJECT_SOURCE_DIR}/../../../../Engine/Dependencies/Celero/include"
    )

set(SOURCE_FILES
    "Source/Main.cpp"
    "Source/PlanetTests.cpp"
    )

source_group("Source" FILES
    ${SOURCE_FILES}
    )

add_executable(ZerothPerformanceTests ${SOURCE_FILES})

set(LINK_LIBRARIES Zeroth Hect Celero)

if(MSVC)
    list(APPEND LINK_LIBRARIES "PowrProf.lib")
else()
    list(APPEND LINK_LIBRARIES "pthread")
endif()

target_link_libraries(ZerothPerformanceTests ${LINK_LIBRARIES})

set_target_properties(ZerothPerformanceTests PROPERTIES
    PROJECT_LABEL ZerothPerformanceTests
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth/Tests"
    )

# Copy settings
add_custom_command(TARGET ZerothPerformanceTests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Settings ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
