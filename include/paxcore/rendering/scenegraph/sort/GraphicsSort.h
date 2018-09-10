//
// Created by Paul on 04.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORT_H
#define PAXENGINE3_RENDERABLESORT_H

#include <vector>
#include <paxcore/rendering/Graphics.h>
#include <paxcore/entity/Entity.h>

namespace PAX {
    namespace Sort {
        template<typename SmallerOperator>
        class GraphicsSort {
            SmallerOperator isSmaller;

        public:
            void sort(std::vector<Graphics*> &graphics) {

                int l = 0;
                int r = graphics.size() - 1;
                int i, j;
                float tempZ;
                Graphics* temp;

                for (i = l + 1; i <= r; ++i) {
                    temp = graphics[i];
                    tempZ = temp->getOwner()->getTransform().z();
                    for (j = i; j > l && isSmaller(tempZ, graphics[j-1]->getOwner()->getTransform().z()); --j) {
                        graphics[j] = graphics[j - 1];
                    }
                    graphics[j] = temp;
                }
            }
        };

        /**
         * This Comparator puts Renderables with greater Z in front of Renderables with smaller Z, so that
         * Renderables far away will be rendered first.
         * This is the comparator to use for 2D applications.
         */
        typedef GraphicsSort<std::less<float>> BackToFrontGraphicsSort;

        /**
         * This Comparator puts Renderables with smaller Z in front of Renderables with greater Z,
         * meaning Renderables in front will be rendered first.
         * This is the comparator to use for 3D applications.
         */
        typedef GraphicsSort<std::greater<float>> FrontToBackGraphicsSort;
    }
}

#endif //PAXENGINE3_RENDERABLESORT_H
