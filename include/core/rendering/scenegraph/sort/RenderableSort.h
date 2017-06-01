//
// Created by Paul on 04.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORT_H
#define PAXENGINE3_RENDERABLESORT_H

#include <vector>
#include "../../Renderable.h"
#include "RenderableSortComparator.h"

namespace PAX {
    namespace Sort {
        class RenderableSort {
        private:
            RenderableSortComparator* _comparator = nullptr;

            void insertionSort(std::vector<Renderable *> &renderables, unsigned int l, unsigned int r);

        public:

            /**
             *
             * @param comparator The comparator to use for sorting. This depends on the use of 2D or 3D
             * rendering. The comparator will be owned to the RenderableSort-Object meaning that the RenderableSort
             * destructor will delete it.
             */
            RenderableSort(RenderableSortComparator* comparator = new BackToFrontRenderableSortComparator);
            ~RenderableSort();

            /**
             * Sets a new comparator. The old one will be deleted.
             */
            void setRenderableSortComparator(RenderableSortComparator* comparator);

            void insertionSort(std::vector<Renderable *> &renderables);
        };
    }
}

#endif //PAXENGINE3_RENDERABLESORT_H
