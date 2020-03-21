add_library(paxrendering
        Renderer.cpp
        Viewport.cpp
        Graphics.cpp
        SceneGraphGraphics.cpp
        RenderOptions.cpp

        camera/Camera.cpp
        camera/Projection.cpp
        camera/PerspectiveProjection.cpp
        camera/PixelScreenProjection.cpp
        camera/FullPixelScreenProjection.cpp

        data/Material.cpp
        data/Asset.cpp
        data/Mesh.cpp
        data/SpriteSheet.cpp

        graphics/AssetGraphics.cpp
        graphics/SpriteGraphics.cpp
        graphics/SpriteSheetGraphics.cpp
        graphics/SceneGraphGraphics.cpp
        graphics/nodes/MeshNode.cpp
        graphics/nodes/TexturingNode.cpp
        graphics/nodes/SpriteSheetNode.cpp

        interface/Renderable.cpp

        light/Light.cpp
        light/DirectionalLight.cpp
        light/SpotLight.cpp
        light/AmbientLight.cpp
        light/PointLight.cpp

        loader/SpriteSheetLoader.cpp
        loader/NullTextureLoader.cpp

        renderpass/RenderPassChannel.cpp
        renderpass/RenderPass.cpp

        resource/Mesh.cpp
        resource/Shader.cpp
        resource/Texture.cpp

        scenegraph/generators/SceneGraphGenerator.cpp
        scenegraph/generators/GroupByShadersSceneGraphGenerator.cpp
        scenegraph/nodes/SortingNode.cpp
        scenegraph/nodes/ShadingNode.cpp
        scenegraph/nodes/TransformationNode.cpp
        scenegraph/generators/SortByZSceneGraphGenerator.cpp
        scenegraph/generators/DefaultSceneGraphGeneratorFactory.cpp
        scenegraph/sort/GraphicsSort.cpp geometry/ScreenFillingQuad.cpp camera/json/ViewportJsonParser.cpp camera/json/ProjectionJsonParser.cpp data/Image.cpp config/PointCloudSettings.cpp data/Colour.cpp)

target_link_libraries(paxrendering paxcore)