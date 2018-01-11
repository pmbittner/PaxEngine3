//
// Created by Paul on 10.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETNODE_H
#define PAXENGINE3_SPRITESHEETNODE_H

#include <core/rendering/resource/Shaded.h>
#include <core/rendering/scenegraph/SceneGraph.h>

namespace PAX {
    class SpriteSheetNode : public SceneGraph, public Shaded {
        glm::ivec2 _offset;
        glm::ivec2 _size;

    public:
        SpriteSheetNode(int columns, int rows);

        void setOffset(int xOffset, int yOffset);
        glm::ivec2 getOffset();
        glm::ivec2 getSize();

        virtual void render(RenderOptions &options) override;
        virtual void registerFlags(Shader::Flags &flags);
        virtual void cacheUniformsFor(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_SPRITESHEETNODE_H
