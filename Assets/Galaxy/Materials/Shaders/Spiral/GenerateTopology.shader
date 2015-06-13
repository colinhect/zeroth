---
base: Galaxy/Materials/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: GenerateTopology.glsl
uniforms:
  - name: seed
    type: Float
  - name: eccentricity
    type: Float
  - name: armThickness
    type: Float
