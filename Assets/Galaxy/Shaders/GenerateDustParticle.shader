---
modules:
  - type: Vertex
    path: Hect/Rendering/Screen.glsl
  - type: Fragment
    path: Noise.glsl
  - type: Fragment
    path: GenerateDustParticle.glsl
uniforms:
  - name: seed
    type: Float
depthTested: true
