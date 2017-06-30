//
// Created by Paul on 08.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORTCOMPARATOR_H
#define PAXENGINE3_RENDERABLESORTCOMPARATOR_H

#include "../../interface/Renderable.h"

namespace PAX {
    namespace Sort {
        class RenderableSortComparator {
        public:
            virtual ~RenderableSortComparator() {}
            virtual bool smaller(Renderable* a, Renderable* b) = 0;
        };

        /**
         * This Comparator puts Renderables with smaller Z in front of Renderables with greater Z,
         * meaning Renderables in front will be rendered first.
         * This is the comparator to use for 3D applications.
         */
        class FrontToBackRenderableSortComparator : public RenderableSortComparator {
        public:
            virtual ~FrontToBackRenderableSortComparator() {}

            virtual inline bool smaller(Renderable* a, Renderable* b) override {
                return a->getZ() < b->getZ();
            }
        };

        /**
         * This Comparator puts Renderables with greater Z in front of Renderables with smaller Z, so that
         * Renderables far away will be rendered first.
         * This is the comparator to use for 2D applications.
         */
        class BackToFrontRenderableSortComparator : public RenderableSortComparator {
        public:
            virtual ~BackToFrontRenderableSortComparator() {}

            virtual inline bool smaller(Renderable* a, Renderable* b) override {
                return a->getZ() > b->getZ();
            }
        };
    }
}

#endif //PAXENGINE3_RENDERABLESORTCOMPARATOR_H
