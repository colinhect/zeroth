project(Zeroth CXX)

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_SOURCE_DIR}/../../Engine/Source"
    )
    
file(GLOB component_files Source/Components/*)
source_group(Source\\Components FILES ${component_files})

file(GLOB systems_files Source/Systems/*)
source_group(Source\\Systems FILES ${systems_files})

file(GLOB files Source/*)
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