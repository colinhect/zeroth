---
base: Hect/Shaders/RenderStages/PostPhysicalGeometry.shader
modules:
  - type: Vertex
    path: Topology.Vertex.glsl
  - type: Fragment
    path: Topology.Fragment.glsl
uniforms:
  - name: modelView
    binding: ModelViewMatrix
  - name: modelViewProjection
    binding: ModelViewProjectionMatrix
  - name: topologyTexture
    type: Texture2
  - name: brightness
    type: Float
    value: 0.01
depthTested: false
blendMode:
  sourceFactor: One
  destinationFactor: One
