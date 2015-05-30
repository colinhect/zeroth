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
depthTested: false
blendMode:
    sourceFactor: One
    destinationFactor: One
