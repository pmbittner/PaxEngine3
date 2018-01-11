//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETGRAPHICS_H
#define PAXENGINE3_SPRITESHEETGRAPHICS_H

#include <core/rendering/graphics/nodes/SpriteSheetNode.h>
#include "core/rendering/Graphics.h"
#include "SpriteGraphics.h"

namespace PAX {
    class SpriteSheetGraphics : public SpriteGraphics {
    protected:
        SpriteSheetNode _spriteSheet;

        virtual void registerFlags(Shader::Flags &flags);
        virtual void initializeTransformation() override;

    public:
        SpriteSheetGraphics(const std::shared_ptr<Texture> &texture, int columns, int rows);

        void setSpritePosition(int x, int y);
        glm::ivec2 getSpritePosition();
        glm::ivec2 getSpriteSheetSize();

        virtual void setShader(std::shared_ptr<Shader> &shader);
    };
}

#endif //PAXENGINE3_SPRITESHEETGRAPHICS_H
