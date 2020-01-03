//
// Created by Paul on 09.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEETGRAPHICS_H
#define PAXENGINE3_SPRITESHEETGRAPHICS_H

#include <paxcore/rendering/scenegraph/nodes/SpriteSheetNode.h>
#include <paxcore/rendering/Graphics.h>
#include "SpriteGraphics.h"
#include "../interface/ShaderFlagsConfigurator.h"

namespace PAX {
    // TODO: Refactor this to use the SpriteSheet class
    class SpriteSheetGraphics : public SpriteGraphics, public ShaderFlagsConfigurator {
        PAX_PROPERTY(SpriteSheetGraphics, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(SpriteGraphics)
        PAX_PROPERTY_IS_SINGLE

        SpriteSheetGraphics();

    protected:
        SpriteSheetNode _spriteSheet;
        int columns = 1, rows = 1;
        glm::ivec2 startPos = glm::ivec2();

        void registerFlags(Shader::Flags &flags) override;
        PAX_NODISCARD glm::vec2 getSpriteSize() const override;

    public:
        SpriteSheetGraphics(const std::shared_ptr<Texture> &texture, int columns, int rows);

        void setSpritePosition(int x, int y);
        void setSpritePosition(const glm::ivec2 & pos);
        PAX_NODISCARD const glm::ivec2 & getSpritePosition() const;
        PAX_NODISCARD const glm::ivec2 & getSpriteSheetSize() const;

        PAX_NODISCARD ClassMetadata getMetadata() override;
    };
}

#endif //PAXENGINE3_SPRITESHEETGRAPHICS_H
