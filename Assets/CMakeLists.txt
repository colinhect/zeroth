project(ZerothAssets)

add_custom_target(ZerothAssets)
    
set_target_properties(ZerothAssets PROPERTIES
    PROJECT_LABEL ZerothAssets
    FOLDER "/Projects/Zeroth"
    )

# Copy assets
add_custom_command(TARGET ZerothAssets
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR} ${OUTPUT_DIR}/Zeroth.data/
    )

# Copy settings
add_custom_command(TARGET ZerothAssets
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/../Settings ${OUTPUT_DIR}/
    )