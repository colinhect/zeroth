---
modules:
  - type: Vertex
    path: Hect/Screen.glsl
  - type: Fragment
    path: Noise.glsl
  - type: Fragment
    path: Particle.glsl
uniforms:
  - name: seed
    type: Float
depthTested: true
