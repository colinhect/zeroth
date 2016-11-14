project(Zeroth CXX)

if(WIN32)
    add_definitions("/D_CRT_SECURE_NO_WARNINGS /DZEROTH_EXPORTS /bigobj")
elseif(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_SOURCE_DIR}/../../Engine/Source"
    )

set(SOURCE
    "Source/Export.h"
    )

source_group("Source" FILES
    ${SOURCE}
    )

set(SOURCE_COMPONENTS
    "Source/Components/BatteryComponent.h"
    "Source/Components/BatterySlotComponent.h"
    "Source/Components/ChaseCameraComponent.h"
    "Source/Components/CockpitCameraComponent.h"
    "Source/Components/GalaxyNodeComponent.h"
    "Source/Components/ObserverCameraComponent.h"
    "Source/Components/PlanetComponent.h"
    "Source/Components/PlanetPatchComponent.h"
    "Source/Components/PlayerShipControlComponent.h"
    "Source/Components/ProxyGalaxyComponent.h"
    "Source/Components/ShipComponent.h"
    "Source/Components/SpiralGalaxyComponent.h"
    "Source/Components/ThrusterComponent.h"
    )

source_group("Source\\Components" FILES
    ${SOURCE_COMPONENTS}
    )

set(SOURCE_SCENES
    "Source/Scenes/CelestialScene.cpp"
    "Source/Scenes/CelestialScene.h"
    "Source/Scenes/GalacticScene.cpp"
    "Source/Scenes/GalacticScene.h"
    "Source/Scenes/SystemicScene.cpp"
    "Source/Scenes/SystemicScene.h"
    "Source/Scenes/ZerothScene.cpp"
    "Source/Scenes/ZerothScene.h"
    )

source_group("Source\\Scenes" FILES
    ${SOURCE_SCENES}
    )

set(SOURCE_SYSTEMS
    "Source/Systems/ChaseCameraSystem.cpp"
    "Source/Systems/ChaseCameraSystem.h"
    "Source/Systems/CockpitCameraSystem.cpp"
    "Source/Systems/CockpitCameraSystem.h"
    "Source/Systems/GalaxySystem.cpp"
    "Source/Systems/GalaxySystem.h"
    "Source/Systems/HudSystem.cpp"
    "Source/Systems/HudSystem.h"
    "Source/Systems/ObserverCameraSystem.cpp"
    "Source/Systems/ObserverCameraSystem.h"
    "Source/Systems/PlanetSystem.cpp"
    "Source/Systems/PlanetSystem.h"
    "Source/Systems/PlayerInputSystem.cpp"
    "Source/Systems/PlayerInputSystem.h"
    "Source/Systems/ProxyGalaxySystem.cpp"
    "Source/Systems/ProxyGalaxySystem.h"
    "Source/Systems/ShipControlSystem.cpp"
    "Source/Systems/ShipControlSystem.h"
    )

source_group("Source\\Systems" FILES
    ${SOURCE_SYSTEMS}
    )

set(SOURCE_FILES
    ${SOURCE}
    ${SOURCE_COMPONENTS}
    ${SOURCE_SCENES}
    ${SOURCE_SYSTEMS}
    )

add_library(Zeroth SHARED ${SOURCE_FILES})
target_link_libraries(Zeroth Hect)

add_subdirectory(${PROJECT_SOURCE_DIR}/Executable)

add_subdirectory(${PROJECT_SOURCE_DIR}/Assets)
add_dependencies(Zeroth ZerothAssets)

add_subdirectory(${PROJECT_SOURCE_DIR}/Settings)
add_dependencies(Zeroth ZerothSettings)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Generated)
add_dependencies(Zeroth ZerothTypes)

add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/PerformanceTests)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/SystemTests)
add_subdirectory(${PROJECT_SOURCE_DIR}/Tests/UnitTests)

set_target_properties(Zeroth PROPERTIES
    PROJECT_LABEL Zeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )
