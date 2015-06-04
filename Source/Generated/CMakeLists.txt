project(ZerothTypes)

add_custom_target(ZerothTypes
    COMMAND python ${PROJECT_SOURCE_DIR}/../../../../Engine/Tools/reflect.py ${PROJECT_SOURCE_DIR}/../ ${PROJECT_SOURCE_DIR} zeroth
    )
    
set_target_properties(ZerothTypes PROPERTIES
    PROJECT_LABEL ZerothTypes
    FOLDER "/Projects/Zeroth"
    )
