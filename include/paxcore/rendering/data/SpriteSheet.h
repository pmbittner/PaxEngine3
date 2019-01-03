//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_SPRITESHEET_H
#define PAXENGINE3_SPRITESHEET_H

#include <vector>
#include <memory>
#include <paxutil/lib/GlmIncludes.h>
#include "Texture.h"

namespace PAX {
    class SpriteSheet {
    protected:
        std::shared_ptr<Texture> texture;
        glm::ivec2 dimensions;

    public:
        SpriteSheet(const std::shared_ptr<Texture>& texture, int columns, int rows);

        const std::shared_ptr<Texture> getTexture();

        /// \return dimensions = (columns, rows)
        glm::ivec2 getDimensions();

        glm::vec2 getCellSize();
    };
}

#endif //PAXENGINE3_SPRITESHEET_H
