# Generated by Build Tool (see Engine/Tools/Build for details)

set(SOURCE
    "Source/./Export.h"
    "Source/./GalaxyGenerator.cpp"
    "Source/./GalaxyGenerator.h"
    "Source/./Main.cpp"
    )

source_group("Source" FILES ${SOURCE})

set(SOURCE_COMPONENTS
    "Source/Components/GalaxyImposterCellComponent.h"
    "Source/Components/PlayerComponent.h"
    )

source_group("Source\\Components" FILES ${SOURCE_COMPONENTS})

set(SOURCE_SCENES
    "Source/Scenes/ClientScene.cpp"
    "Source/Scenes/ClientScene.h"
    "Source/Scenes/IntergalacticScene.cpp"
    "Source/Scenes/IntergalacticScene.h"
    "Source/Scenes/InterstellarScene.cpp"
    "Source/Scenes/InterstellarScene.h"
    "Source/Scenes/StellarScene.cpp"
    "Source/Scenes/StellarScene.h"
    )

source_group("Source\\Scenes" FILES ${SOURCE_SCENES})

set(SOURCE_SYSTEMS
    "Source/Systems/GalaxyImposterSystem.cpp"
    "Source/Systems/GalaxyImposterSystem.h"
    "Source/Systems/HudSystem.cpp"
    "Source/Systems/HudSystem.h"
    "Source/Systems/PlayerInputSystem.cpp"
    "Source/Systems/PlayerInputSystem.h"
    )

source_group("Source\\Systems" FILES ${SOURCE_SYSTEMS})

set(SOURCE_FILES
    ${SOURCE}
    ${SOURCE_COMPONENTS}
    ${SOURCE_SCENES}
    ${SOURCE_SYSTEMS}
    )

