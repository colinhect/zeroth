# Generated by Build Tool (see Engine/Tools/Build for details)

set(SOURCE
    "Source/./Export.h"
    "Source/./Main.cpp"
    "Source/./TextureGenerator.cpp"
    "Source/./TextureGenerator.h"
    )

source_group("Source" FILES ${SOURCE})

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

source_group("Source\\Components" FILES ${SOURCE_COMPONENTS})

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

source_group("Source\\Scenes" FILES ${SOURCE_SCENES})

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

source_group("Source\\Systems" FILES ${SOURCE_SYSTEMS})

set(SOURCE_FILES
    ${SOURCE}
    ${SOURCE_COMPONENTS}
    ${SOURCE_SCENES}
    ${SOURCE_SYSTEMS}
    )

