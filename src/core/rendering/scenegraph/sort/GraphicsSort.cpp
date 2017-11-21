//
// Created by Paul on 04.05.2017.
//

#include "core/rendering/scenegraph/sort/GraphicsSort.h"
#include <cassert>
#include <iostream>

namespace PAX {
    namespace Sort {
        GraphicsSort::GraphicsSort(GraphicsSortComparator *comparator) : _comparator(comparator) {
            assert(comparator);
        }

        GraphicsSort::~GraphicsSort() {
            delete _comparator;
        }

        void GraphicsSort::setGraphicsSortComparator(GraphicsSortComparator *comparator) {
            assert(comparator);
            delete (_comparator);
            _comparator = comparator;
        }

        void GraphicsSort::insertionSort(std::vector<Graphics*> &graphics, int l, int r) {
            int i, j;
            for (i = l + 1; i <= r; ++i) {
                Graphics *temp = graphics[i];
                for (j = i; j > l && _comparator->smaller(temp, graphics[j-1]); --j)
                    graphics[j] = graphics[j-1];
                graphics[j] = temp;
            }
        }

        void GraphicsSort::insertionSort(std::vector<Graphics*> &graphics) {
            insertionSort(graphics, 0, graphics.size() - 1);
        }
    }
}