---
renderStage: PostPhysicalGeometry
modules:
  - type: Vertex
    path: Star.Vertex.glsl
  - type: Fragment
    path: Star.Fragment.glsl
uniforms:
  - name: cameraPosition
    binding: CameraPosition
  - name: model
    binding: ModelMatrix
  - name: modelViewProjection
    binding: ModelViewProjectionMatrix
  - name: starTexture
    type: Texture2
  - name: sizeRange
    type: Vector2
    value: [ 1.0, 4.0 ]
  - name: brightnessRange
    type: Vector2
    value: [ 0.1, 64.0 ]
depthTested: false
blendMode:
    sourceFactor: One
    destinationFactor: One
