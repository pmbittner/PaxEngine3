//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORTCOMPARATOR_H
#define PAXENGINE3_RENDERABLESORTCOMPARATOR_H

#include "../../interface/Renderable.h"
#include <core/entity/Entity.h>

namespace PAX {
    namespace Sort {
        class GraphicsSortComparator {
        public:
            virtual ~GraphicsSortComparator() {}
            virtual bool smaller(Graphics* a, Graphics* b) = 0;
        };

        /**
         * This Comparator puts Renderables with smaller Z in front of Renderables with greater Z,
         * meaning Renderables in front will be rendered first.
         * This is the comparator to use for 3D applications.
         */
        class FrontToBackGraphicsSortComparator : public GraphicsSortComparator {
        public:
            virtual ~FrontToBackGraphicsSortComparator() {}

            virtual inline bool smaller(Graphics* a, Graphics* b) override {
                return a->getOwner()->getTransform().z() < b->getOwner()->getTransform().z();
            }
        };

        /**
         * This Comparator puts Renderables with greater Z in front of Renderables with smaller Z, so that
         * Renderables far away will be rendered first.
         * This is the comparator to use for 2D applications.
         */
        class BackToFrontGraphicsSortComparator : public GraphicsSortComparator {
        public:
            virtual ~BackToFrontGraphicsSortComparator() {}

            virtual inline bool smaller(Graphics* a, Graphics* b) override {
                return a->getOwner()->getTransform().z() > b->getOwner()->getTransform().z();
            }
        };
    }
}

#endif //PAXENGINE3_RENDERABLESORTCOMPARATOR_H
