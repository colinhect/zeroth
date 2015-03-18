---
base: Galaxy/Shaders/Procedural.shader
modules:
  - type: Fragment
    path: CenterParticle.glsl
uniforms:
  - name: seed
    type: Float
  - name: color
    type: Color
    value: [ 0.874, 0.85, 0.77 ]
