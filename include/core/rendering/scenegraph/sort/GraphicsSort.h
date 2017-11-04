//
// Created by Paul on 04.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORT_H
#define PAXENGINE3_RENDERABLESORT_H

#include <vector>
#include <core/rendering/Graphics.h>
#include "GraphicsSortComparator.h"

namespace PAX {
    namespace Sort {
        class GraphicsSort {
        private:
            GraphicsSortComparator* _comparator = nullptr;

            void insertionSort(std::vector<Graphics*> &graphics, int l, int r);

        public:

            /**
             *
             * @param comparator The comparator to use for sorting. This depends on the use of 2D or 3D
             * rendering. The comparator will be owned to the RenderableSort-Object meaning that the RenderableSort
             * destructor will delete it.
             */
            GraphicsSort(GraphicsSortComparator* comparator = new BackToFrontGraphicsSortComparator);
            ~GraphicsSort();

            /**
             * Sets a new comparator. The old one will be deleted.
             */
            void setGraphicsSortComparator(GraphicsSortComparator* comparator);

            void insertionSort(std::vector<Graphics*> &graphics);
        };
    }
}

#endif //PAXENGINE3_RENDERABLESORT_H
