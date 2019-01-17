# Concepts

## Render Pipeline Overview

1. renderer.render(scene)
2. for each layer in the scene
3. for each active camera, a render queue is constructed for all of the scene objects within its view frustum
4. a render context consisting of the camera, layer, and queue is passed to the camera's compositor's render()
5. for each render pass in the compositor, the render context is passed to the render pass's render()
6. implementation of render pass's render() is currently up to user implementation.

## Subframe Interpolation (Tweening)

A real-time graphical application should perform logic updates at a fixed interval with a constant timestep (dt). The rendering process, however, should run as many times as the hardware is capable of before the next logic update is scheduled. Each time the scene is rendered, any shader variables that change over time should be interpolated between their previous and current states. This technique can achieve smooth visuals even at a very low update rate.

# Shader Templates and Permutations

The shader system generates different permutations of shaders to satisfy the rendering requirements of different material types, vertex formats, and lighting modes. Data such as a material opacity flag or the maximum number of point lights can be stored in a single 32-bit bit field. A shader permutation will be generated for each unique value of this bit field, with the __PERMUTATION__ shader preprocessor definition used to selectively enable functionality before compilation. For example, a shader can extract bit flags from __PERMUTATION__ to determine whether the geometry is skinned or not, then use preprocessor conditionals to choose the appropriate vertex transformation functions. This way the shader only needs to be written once but will support a variety of rendering contexts.

The written shader file may be referred to as a "shader template", and the automatically generated shader as a "shader permutation".

