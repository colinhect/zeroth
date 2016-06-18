project(ZerothSystemTests CXX)

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
    "Source/Main.cpp"
    )
    
add_executable(ZerothSystemTests ${SOURCE_FILES})
    
target_link_libraries(ZerothSystemTests Zeroth Hect)
    
set_target_properties(ZerothSystemTests PROPERTIES
    PROJECT_LABEL ZerothSystemTests
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth/Tests"
    )

# Copy settings
add_custom_command(TARGET ZerothSystemTests
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Settings ${OUTPUT_DIR}/
    )
