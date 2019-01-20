//
// Created by paul on 07.01.19.
//

#include "platformerdemo/behaviour/Dance2D.h"

namespace PAX {
    PAX_PROPERTY_SOURCE(PAX::Dance2D, PAX_PROPERTY_IS_CONCRETE)

    Dance2D * Dance2D::createFromProvider(ContentProvider & provider) {
        return new Dance2D();
    }

    void Dance2D::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}