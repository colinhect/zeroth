project(ZerothTypes)

add_custom_target(ZerothTypes)
    
set_target_properties(ZerothTypes PROPERTIES
    PROJECT_LABEL ZerothTypes
    FOLDER "/Projects/Zeroth"
    )

# Generate reflection code
add_custom_command(TARGET ZerothTypes
    PRE_BUILD
    COMMAND python ${PROJECT_SOURCE_DIR}/../../../../Engine/Tools/reflect.py ${PROJECT_SOURCE_DIR}/../ ${PROJECT_SOURCE_DIR} zeroth
    )
