---
base: Galaxy/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: MedianParticle.glsl
uniforms:
  - name: seed
    type: Float
  - name: color
    type: Color
    value: [ 0.62, 0.71, 0.86 ]
