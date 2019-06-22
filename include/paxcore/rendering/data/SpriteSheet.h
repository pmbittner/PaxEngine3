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

        const std::shared_ptr<Texture> getTexture() const;

        /// \return dimensions = (columns, rows)
        const glm::ivec2 & getDimensions() const;

        glm::vec2 getCellSize() const;
    };
}

#endif //PAXENGINE3_SPRITESHEET_H
