add_library(paxrendering
        Renderer.cpp
        Viewport.cpp
        graphics/nodes/TexturingNode.cpp
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
        graphics/nodes/MeshNode.cpp
        scenegraph/sort/GraphicsSort.cpp

        resource/Mesh.cpp
        resource/Shader.cpp
        resource/Texture.cpp
        resource/SpriteSheet.cpp
        scenegraph/nodes/TransformationNode.cpp
        scenegraph/generators/GroupByShadersAndSortByZSceneGraphGenerator.cpp
        graphics/SpriteGraphics.cpp
        graphics/SpriteSheetGraphics.cpp graphics/nodes/SpriteSheetNode.cpp)