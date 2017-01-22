project(Zeroth CXX)

if(WIN32)
    add_definitions("/D_CRT_SECURE_NO_WARNINGS /DZEROTH_EXPORTS /bigobj")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_SOURCE_DIR}/../../Engine/Source"
    )

include(Sources.cmake)

add_library(Zeroth SHARED ${SOURCE_FILES})
target_link_libraries(Zeroth Hect)

add_subdirectory(${PROJECT_SOURCE_DIR}/Executable)

add_subdirectory(${PROJECT_SOURCE_DIR}/Assets)
add_dependencies(Zeroth ZerothAssets)

add_subdirectory(${PROJECT_SOURCE_DIR}/Settings)
add_dependencies(Zeroth ZerothSettings)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Generated)
add_dependencies(Zeroth ZerothTypes)

add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/PerformanceTests)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/SystemTests)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/UnitTests)

set_target_properties(Zeroth PROPERTIES
    PROJECT_LABEL Zeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )
