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
    value: [ 0.25, 1.5 ]
  - name: brightnessRange
    type: Vector2
    value: [ 0.00001, 100.0 ]
depthTested: false
blendMode:
    sourceFactor: One
    destinationFactor: One
