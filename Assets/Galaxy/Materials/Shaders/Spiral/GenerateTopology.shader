---
base: Galaxy/Materials/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: GenerateTopology.glsl
uniforms:
  - name: seed
    type: Float
  - name: bulgeColor
    type: Color
  - name: primaryColor
    type: Color
  - name: secondaryColor
    type: Color
  - name: variation0
    type: Float
  - name: variation1
    type: Float
  - name: variation2
    type: Float
  - name: variation3
    type: Float
