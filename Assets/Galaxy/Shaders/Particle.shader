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
  - name: modelViewProjection
    binding: ModelViewProjectionMatrix
  - name: renderTargetSize
    binding: RenderTargetSize
  - name: particleTexture
    type: Texture2
depthTested: false
blendMode:
    sourceFactor: One
    destinationFactor: One
