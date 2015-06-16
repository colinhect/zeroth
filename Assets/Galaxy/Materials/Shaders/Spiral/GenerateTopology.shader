---
base: Galaxy/Materials/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: GenerateTopology.glsl
uniforms:
  - name: seed
    type: Float
