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

        void RenderableSort::insertionSort(std::vector<Renderable *> *renderables) {

        }
    }
}