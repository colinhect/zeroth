project(Zeroth CXX)

if(UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y -Wall")
endif()

include_directories(
    "${PROJECT_SOURCE_DIR}/Source"
    "${PROJECT_SOURCE_DIR}/../../Engine/Source"
    )
    
set(SOURCE_FILES
    "Source/Main.cpp"
    "Source/Components/CockpitCamera.h"
    "Source/Components/GalaxyNode.h"
    "Source/Components/ObserverCamera.h"
    "Source/Components/Planetoid.h"
    "Source/Components/PlanetoidPatch.h"
    "Source/Components/PlayerShipControl.h"
    "Source/Components/ProxyGalaxy.h"
    "Source/Components/Ship.h"
    "Source/Components/SpiralGalaxy.h"
    "Source/Components/Thruster.h"
    "Source/Systems/CockpitCameraSystem.cpp"
    "Source/Systems/CockpitCameraSystem.h"
    "Source/Systems/GalaxySystem.cpp"
    "Source/Systems/GalaxySystem.h"
    "Source/Systems/HudSystem.cpp"
    "Source/Systems/HudSystem.h"
    "Source/Systems/ObserverCameraSystem.cpp"
    "Source/Systems/ObserverCameraSystem.h"
    "Source/Systems/PlanetoidSystem.cpp"
    "Source/Systems/PlanetoidSystem.h"
    "Source/Systems/PlayerInputSystem.cpp"
    "Source/Systems/PlayerInputSystem.h"
    "Source/Systems/ProxyGalaxySystem.cpp"
    "Source/Systems/ProxyGalaxySystem.h"
    "Source/Systems/ShipControlSystem.cpp"
    "Source/Systems/ShipControlSystem.h"
    )
    
source_group("Source" FILES
    "Source/Main.cpp"
    )
    
source_group("Source\\Components" FILES
    "Source/Components/CockpitCamera.h"
    "Source/Components/GalaxyNode.h"
    "Source/Components/ObserverCamera.h"
    "Source/Components/Planetoid.h"
    "Source/Components/PlanetoidPatch.h"
    "Source/Components/PlayerShipControl.h"
    "Source/Components/ProxyGalaxy.h"
    "Source/Components/Ship.h"
    "Source/Components/SpiralGalaxy.h"
    "Source/Components/Thruster.h"
    )

source_group("Source\\Systems" FILES
    "Source/Systems/CockpitCameraSystem.cpp"
    "Source/Systems/CockpitCameraSystem.h"
    "Source/Systems/GalaxySystem.cpp"
    "Source/Systems/GalaxySystem.h"
    "Source/Systems/HudSystem.cpp"
    "Source/Systems/HudSystem.h"
    "Source/Systems/ObserverCameraSystem.cpp"
    "Source/Systems/ObserverCameraSystem.h"
    "Source/Systems/PlanetoidSystem.cpp"
    "Source/Systems/PlanetoidSystem.h"
    "Source/Systems/PlayerInputSystem.cpp"
    "Source/Systems/PlayerInputSystem.h"
    "Source/Systems/ProxyGalaxySystem.cpp"
    "Source/Systems/ProxyGalaxySystem.h"
    "Source/Systems/ShipControlSystem.cpp"
    "Source/Systems/ShipControlSystem.h"
    )

add_executable(Zeroth ${SOURCE_FILES})

add_subdirectory(${PROJECT_SOURCE_DIR}/Assets)
add_dependencies(Zeroth ZerothAssets)

add_subdirectory(${PROJECT_SOURCE_DIR}/Settings)
add_dependencies(Zeroth ZerothSettings)

add_subdirectory(${PROJECT_SOURCE_DIR}/Source/Generated)
add_dependencies(Zeroth ZerothTypes)
    
target_link_libraries(Zeroth Hect)
    
set_target_properties(Zeroth PROPERTIES
    PROJECT_LABEL Zeroth
    LINKER_LANGUAGE CXX
    FOLDER "/Projects/Zeroth"
    )