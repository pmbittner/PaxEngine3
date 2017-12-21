add_library(paxrendering
        Renderer.cpp
        Viewport.cpp
        scenegraph/nodes/TexturingNode.cpp
        Graphics.cpp
        SceneGraphGraphics.cpp
        RenderOptions.cpp

        camera/Camera.cpp
        camera/Projection.cpp
        camera/PerspectiveProjection.cpp
        camera/PixelScreenProjection.cpp
        camera/FullPixelScreenProjection.cpp

        scenegraph/SceneGraphGenerator.cpp
        scenegraph/generators/GroupByShadersSceneGraphGenerator.cpp
        scenegraph/nodes/SortingNode.cpp
        scenegraph/nodes/ShadingNode.cpp
        scenegraph/nodes/MeshNode.cpp
        scenegraph/sort/GraphicsSort.cpp

        resource/Mesh.cpp
        resource/Shader.cpp
        resource/Texture.cpp)