project(ZerothSettings)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${CMAKE_BUILD_TYPE})

add_custom_target(ZerothSettings
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )
    
set_target_properties(ZerothSettings PROPERTIES
    PROJECT_LABEL ZerothSettings
    FOLDER "/Projects/Zeroth"
    )
