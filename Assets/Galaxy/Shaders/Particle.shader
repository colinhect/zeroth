---
renderStage: PostPhysicalGeometry
modules:
  - type: Vertex
    path: Particle.Vertex.glsl
  - type: Geometry
    path: Particle.Geometry.glsl
  - type: Fragment
    path: Particle.Fragment.glsl
uniforms:
  - name: model
    binding: ModelMatrix
  - name: viewProjection
    binding: ViewProjectionMatrix
  - name: cameraPosition
    binding: CameraPosition
  - name: particleTexture
    type: Texture2
  - name: brightness
    type: Float
    value: 0.0008
depthTested: false
blendMode:
  sourceFactor: One
  destinationFactor: One
