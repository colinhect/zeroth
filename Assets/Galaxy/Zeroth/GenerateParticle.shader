---
modules:
  - type: Vertex
    path: Hect/Rendering/Screen.glsl
  - type: Fragment
    path: Galaxy/Shaders/Noise.glsl
  - type: Fragment
    path: GenerateParticle.glsl
uniforms:
  - name: seed
    type: Float
depthTested: true
