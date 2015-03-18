---
base: Galaxy/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: MedianDensity.glsl
uniforms:
  - name: spiralFactor
    type: Float
    value: 24.0
