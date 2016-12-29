project(ZerothUnitTests CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall -Wextra -Werror -pedantic")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/../../Source"
    "${PROJECT_SOURCE_DIR}/../../../../Engine/Dependencies/Catch"
    )

set(SOURCE_FILES
    "Source/Main.cpp"
    )

source_group("Source" FILES
    ${SOURCE_FILES}
    )

add_executable(ZerothUnitTests ${SOURCE_FILES})

target_link_libraries(ZerothUnitTests Zeroth Hect)

set_target_properties(ZerothUnitTests PROPERTIES
    PROJECT_LABEL ZerothUnitTests
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth/Tests"
    )
