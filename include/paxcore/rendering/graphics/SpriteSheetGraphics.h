//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETGRAPHICS_H
#define PAXENGINE3_SPRITESHEETGRAPHICS_H

#include <paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h>
#include <paxcore/rendering/Graphics.h>
#include "SpriteGraphics.h"

namespace PAX {
    class SpriteSheetGraphics : public SpriteGraphics {
        PAX_ENTITYCOMPONENT_BODY(SpriteGraphics, false)

    protected:
        SpriteSheetNode _spriteSheet;

        virtual void registerFlags(Shader::Flags &flags);
        virtual glm::vec2 getSpriteSize() const override;

    public:
        SpriteSheetGraphics(const std::shared_ptr<Texture> &texture, int columns, int rows);

        void setSpritePosition(int x, int y);
        glm::ivec2 getSpritePosition() const;
        glm::ivec2 getSpriteSheetSize() const;

        virtual void setShader(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_SPRITESHEETGRAPHICS_H
