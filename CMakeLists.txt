include_directories(
    "${PROJECT_SOURCE_DIR}/Projects/Zeroth/Source"
    "${PROJECT_SOURCE_DIR}/Hect/Source"
    "${PROJECT_SOURCE_DIR}/Dependencies/Catch"
    )
    
FILE(GLOB component_files Source/Components/*)
source_group(Source\\Components FILES ${component_files})

FILE(GLOB systems_files Source/Systems/*)
source_group(Source\\Systems FILES ${systems_files})

FILE(GLOB files Source/*)
source_group(Source FILES ${files})
    
add_executable(Zeroth
    "Source/Components/CockpitCamera.h"
    "Source/Components/PlayerCamera.h"
    "Source/Components/PlayerShipControl.h"
    "Source/Components/Ship.cpp"
    "Source/Components/Ship.h"
    "Source/Components/Thruster.cpp"
    "Source/Components/Thruster.h"
    "Source/Systems/CockpitCameraSystem.cpp"
    "Source/Systems/CockpitCameraSystem.h"
    "Source/Systems/PlayerCameraSystem.cpp"
    "Source/Systems/PlayerCameraSystem.h"
    "Source/Systems/PlayerShipControlSystem.cpp"
    "Source/Systems/PlayerShipControlSystem.h"
    "Source/Systems/ShipControlSystem.cpp"
    "Source/Systems/ShipControlSystem.h"
    "Source/Main.cpp"
    "Source/ZerothGameMode.cpp"
    "Source/ZerothGameMode.h"
    )
    
target_link_libraries(Zeroth Hect)
    
set_target_properties(Zeroth PROPERTIES
    PROJECT_LABEL Zeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Zeroth"
    )


add_custom_command(TARGET Zeroth
    PRE_BUILD
    COMMAND python ${PROJECT_SOURCE_DIR}/Hect/Tools/reflect.py ${PROJECT_SOURCE_DIR}/Projects/Zeroth/Source/ ${PROJECT_SOURCE_DIR}/Projects/Zeroth/Source/Generated/ zeroth
    )

add_custom_command(TARGET Zeroth
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Projects/Zeroth/Assets ${HECT_OUTPUT_DIR}/Zeroth.data/
    )

add_custom_command(TARGET Zeroth
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${PROJECT_SOURCE_DIR}/Projects/Zeroth/Config ${HECT_OUTPUT_DIR}/
    )