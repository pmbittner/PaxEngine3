//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETGRAPHICS_H
#define PAXENGINE3_SPRITESHEETGRAPHICS_H

#include <paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h>
#include <paxcore/rendering/Graphics.h>
#include "SpriteGraphics.h"

namespace PAX {
    // TODO: Refactor this to use the SpriteSheet class
    class SpriteSheetGraphics : public SpriteGraphics {
        PAX_PROPERTY(SpriteSheetGraphics, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(SpriteGraphics)
        PAX_PROPERTY_IS_SINGLE

        SpriteSheetGraphics();
        void init();

    protected:
        SpriteSheetNode _spriteSheet;
        int columns = 1, rows = 1;
        glm::ivec2 startPos = glm::ivec2();

        PAX_NODISCARD glm::vec2 getSpriteSize() const override;

    public:
        SpriteSheetGraphics(const std::shared_ptr<Texture> &texture, int columns, int rows);

        void setSpritePosition(int x, int y);
        void setSpritePosition(const glm::ivec2 & pos);
        PAX_NODISCARD const glm::ivec2 & getSpritePosition() const;
        PAX_NODISCARD const glm::ivec2 & getSpriteSheetSize() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
        void created() override;
    };
}

#endif //PAXENGINE3_SPRITESHEETGRAPHICS_H
