project(ZerothAssets)

add_custom_target(ZerothAssets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR} ${OUTPUT_DIR}/Zeroth.data/
    )
    
set_target_properties(ZerothAssets PROPERTIES
    PROJECT_LABEL ZerothAssets
    FOLDER "/Projects/Zeroth"
    )
