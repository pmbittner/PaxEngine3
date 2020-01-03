//
// Created by paul on 07.01.19.
//

#include "platformerdemo/behaviour/DragNDrop.h"

namespace PAX {
    PAX_PROPERTY_INIT(PAX::DragNDrop, PAX_PROPERTY_IS_CONCRETE)

    DragNDrop * DragNDrop::createFromProvider(ContentProvider & provider) {
        return new DragNDrop();
    }

    void DragNDrop::initializeFromProvider(ContentProvider & provider) {
        Super::initializeFromProvider(provider);
    }
}