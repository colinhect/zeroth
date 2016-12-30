project(ZerothAssets)

include(Sources.cmake)

add_custom_target(ZerothAssets
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Zeroth.data/
    SOURCES ${SOURCE_FILES}
    )

set_target_properties(ZerothAssets PROPERTIES
    PROJECT_LABEL ZerothAssets
    FOLDER "/Projects/Zeroth"
    )
