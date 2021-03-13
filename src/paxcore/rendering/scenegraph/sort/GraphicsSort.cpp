//
// Created by Paul on 04.05.2017.
//

#include <paxcore/rendering/scenegraph/sort/GraphicsSort.h>
#include <cassert>
#include <iostream>

namespace PAX {
    namespace Sort {
        // TODO: ->getOwner()->getTransformation() might be inefficient

        bool IsAInFrontOfB(Graphics* a, Graphics* b) {
            float zA = a->getOwner()->getTransformation().z();
            float zB = b->getOwner()->getTransformation().z();
            return zA < zB || (zA == zB && a < b); // compare pointers as second priority for cache optimization
        }

        bool IsBInFrontOfA(Graphics* a, Graphics* b) {
            float zA = a->getOwner()->getTransformation().z();
            float zB = b->getOwner()->getTransformation().z();
            return zB < zA || (zA == zB && a < b); // compare pointers as second priority for cache optimization
        }
    }
}