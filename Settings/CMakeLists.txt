project(ZerothSettings)

add_custom_target(ZerothSettings
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR} ${OUTPUT_DIR}/
    )
    
set_target_properties(ZerothSettings PROPERTIES
    PROJECT_LABEL ZerothSettings
    FOLDER "/Projects/Zeroth"
    )
