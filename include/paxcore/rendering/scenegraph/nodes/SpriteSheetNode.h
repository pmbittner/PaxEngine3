//
// Created by Paul on 10.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETNODE_H
#define PAXENGINE3_SPRITESHEETNODE_H

#include <paxcore/rendering/interface/ShaderFlagsConfigurator.h>
#include <paxcore/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class SpriteSheetNode : public SceneGraph, public ShaderFlagsConfigurator {
        glm::ivec2 _offset{};
        glm::ivec2 _size;

    public:
        SpriteSheetNode(int columns, int rows);

        void setOffset(int xOffset, int yOffset);
        PAX_NODISCARD const glm::ivec2 & getOffset() const;
        void setSize(const glm::ivec2 & size);
        PAX_NODISCARD const glm::ivec2 & getSize() const;

        void render(RenderOptions &options) override;
        void registerFlags(Shader::Flags &flags) override;
    };
}

#endif //PAXENGINE3_SPRITESHEETNODE_H
