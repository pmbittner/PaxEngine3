//
// Created by Paul on 21.05.2019.
//

#ifndef PAXENGINE3_CHARACTERORIENTATION_H
#define PAXENGINE3_CHARACTERORIENTATION_H

#include <paxcore/entity/GameEntityProperty.h>

namespace PAX::Tiles {
    class CharacterOrientation : public GameEntityProperty {
        PAX_PROPERTY(CharacterOrientation, PAX_PROPERTY_IS_CONCRETE)
        PAX_PROPERTY_DERIVES(GameEntityProperty)
        PAX_PROPERTY_IS_SINGLE

        glm::vec2 facingDirection;

    public:
        CharacterOrientation();
        ~CharacterOrientation() override;

        const glm::vec2 & getFacingDirection() const;
        void setFacingDirection(const glm::vec2 & dir);
    };
}

#endif //PAXENGINE3_CHARACTERORIENTATION_H
