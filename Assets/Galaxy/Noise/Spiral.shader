---
modules:
  - type: Vertex
    path: Hect/Screen.glsl
  - type: Fragment
    path: Common/Noise.glsl
  - type: Fragment
    path: Spiral.glsl
uniforms:
  - name: seed
    type: Float
depthTested: true
