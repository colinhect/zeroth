---
base: Procedural.shader
modules:
  - type: Fragment
    path: GenerateSpiral.glsl
uniforms:
  - name: seed
    type: Float
  - name: eccentricity
    type: Float
  - name: armThickness
    type: Float
