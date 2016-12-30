# Generated by generate_sources.py

set(SOURCE
    "./CMakeLists.txt"
    )

set(SOURCE_GALAXY_MATERIALS
    "Galaxy/Materials/Star.Fragment.glsl"
    "Galaxy/Materials/Star.material"
    "Galaxy/Materials/Star.png"
    "Galaxy/Materials/Star.shader"
    "Galaxy/Materials/Star.texture2"
    "Galaxy/Materials/Star.Vertex.glsl"
    )

source_group("Galaxy\\Materials" FILES ${SOURCE_GALAXY_MATERIALS})

set(SOURCE_GALAXY_SHADERS
    "Galaxy/Shaders/Particle.Fragment.glsl"
    "Galaxy/Shaders/Particle.Geometry.glsl"
    "Galaxy/Shaders/Particle.shader"
    "Galaxy/Shaders/Particle.Vertex.glsl"
    "Galaxy/Shaders/Topology.Fragment.glsl"
    "Galaxy/Shaders/Topology.shader"
    "Galaxy/Shaders/Topology.Vertex.glsl"
    )

source_group("Galaxy\\Shaders" FILES ${SOURCE_GALAXY_SHADERS})

set(SOURCE_MODULES_BATTERIES
    "Modules/Batteries/EnthegisStandard60V.entity"
    )

source_group("Modules\\Batteries" FILES ${SOURCE_MODULES_BATTERIES})

set(SOURCE_SCENES
    "Scenes/BaseGalactic.scene"
    "Scenes/Master.scene"
    "Scenes/ProxyGalaxy.scene"
    )

source_group("Scenes" FILES ${SOURCE_SCENES})

set(SOURCE_SCENES_BASE
    "Scenes/Base/Base.scene"
    "Scenes/Base/ProxyGalaxyBase.scene"
    )

source_group("Scenes\\Base" FILES ${SOURCE_SCENES_BASE})

set(SOURCE_SCENES_TEST
    "Scenes/Test/Interface.scene"
    "Scenes/Test/Local.scene"
    "Scenes/Test/Planet.scene"
    "Scenes/Test/Simple.scene"
    )

source_group("Scenes\\Test" FILES ${SOURCE_SCENES_TEST})

set(SOURCE_SHIPS
    "Ships/CockpitCamera.entity"
    "Ships/Indor.Cockpit.entity"
    "Ships/Indor.entity"
    "Ships/Indor.Hull.material"
    "Ships/Indor.Hull.mesh"
    "Ships/Indor.Screen.mesh"
    "Ships/Indor.ScreenFrame.mesh"
    "Ships/Indor.Seat.mesh"
    )

source_group("Ships" FILES ${SOURCE_SHIPS})

set(SOURCE_TEST
    "Test/Cube.Main.mesh"
    "Test/MetalCrate.Diffuse.png"
    "Test/MetalCrate.Diffuse.texture2"
    "Test/MetalCrate.material"
    "Test/MetalCrate.Material.png"
    "Test/MetalCrate.Material.texture2"
    "Test/MetalCrate.Normal.png"
    "Test/MetalCrate.Normal.texture2"
    "Test/Observer.entity"
    )

source_group("Test" FILES ${SOURCE_TEST})

set(SOURCE_TEXTUREGENERATOR
    "TextureGenerator/GlowParticle.glsl"
    "TextureGenerator/GlowParticle.shader"
    "TextureGenerator/Noise.glsl"
    "TextureGenerator/Procedural.glsl"
    "TextureGenerator/Procedural.shader"
    "TextureGenerator/SpiralTopology.glsl"
    "TextureGenerator/SpiralTopology.shader"
    )

source_group("TextureGenerator" FILES ${SOURCE_TEXTUREGENERATOR})

set(SOURCE_WORKING
    "Working/1.blend"
    "Working/Assaulter.blend"
    "Working/Cube.blend"
    "Working/Cube2.blend"
    "Working/Indor.Baked.blend"
    "Working/Indor.blend"
    "Working/New1.blend"
    "Working/SensorProbe.blend"
    "Working/Squid.blend"
    )

source_group("Working" FILES ${SOURCE_WORKING})

set(SOURCE_FILES
    ${SOURCE}
    ${SOURCE_GALAXY_MATERIALS}
    ${SOURCE_GALAXY_SHADERS}
    ${SOURCE_MODULES_BATTERIES}
    ${SOURCE_SCENES}
    ${SOURCE_SCENES_BASE}
    ${SOURCE_SCENES_TEST}
    ${SOURCE_SHIPS}
    ${SOURCE_TEST}
    ${SOURCE_TEXTUREGENERATOR}
    ${SOURCE_WORKING}
    )

