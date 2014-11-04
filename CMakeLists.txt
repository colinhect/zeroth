project(Zeroth CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_SOURCE_DIR}/../../Engine/Source"
    )

grouped_source_files(SOURCE_FILES ${PROJECT_SOURCE_DIR}/Source)
add_executable(Zeroth ${SOURCE_FILES})

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Generated)
add_dependencies(Zeroth ZerothTypes)
    
target_link_libraries(Zeroth Hect)
    
set_target_properties(Zeroth PROPERTIES
    PROJECT_LABEL Zeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )

add_custom_command(TARGET Zeroth
    PRE_BUILD
    COMMAND python ${PROJECT_SOURCE_DIR}/../../Engine/Tools/reflect.py ${PROJECT_SOURCE_DIR}/Source/ ${PROJECT_SOURCE_DIR}/Source/Generated/ zeroth
    )

add_custom_command(TARGET Zeroth
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Assets ${OUTPUT_DIR}/Zeroth.data/
    )

add_custom_command(TARGET Zeroth
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Config ${OUTPUT_DIR}/
    )