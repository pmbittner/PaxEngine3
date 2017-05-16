//
// Created by Paul on 04.05.2017.
//

#include "../../../../../include/core/rendering/scenegraph/sort/RenderableSort.h"
#include <cassert>

namespace PAX {
    namespace Sort {
        RenderableSort::RenderableSort(RenderableSortComparator *comparator) : _comparator(comparator) {
            assert(_comparator);
        }

        RenderableSort::~RenderableSort() {
            delete _comparator;
        }

        void RenderableSort::setRenderableSortComparator(RenderableSortComparator *comparator) {
            assert(comparator);
            delete (_comparator);
            _comparator = comparator;
        }

        void RenderableSort::insertionSort(std::vector<Renderable *> &renderables, unsigned int l, unsigned int r) {
            int i, j;
            for (i = l + 1; i <= r; ++i) {
                Renderable *temp = renderables[i];
                for (j = i; j > l && _comparator->smaller(temp, renderables[j-1]); --j)
                    renderables[j] = renderables[j-1];
                renderables[j] = temp;
            }
        }

        void RenderableSort::insertionSort(std::vector<Renderable *> &renderables) {
            insertionSort(renderables, 0, renderables.size() - 1);
        }
    }
}