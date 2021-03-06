//
// Created by Paul on 04.05.2017.
//

#ifndef PAXENGINE3_RENDERABLESORT_H
#define PAXENGINE3_RENDERABLESORT_H

#include <vector>
#include <paxcore/rendering/Graphics.h>
#include <paxcore/gameentity/GameEntity.h>

namespace PAX {
    namespace Sort {
        template<bool isSmaller(Graphics*,Graphics*)>
        struct GraphicsSort {
            static void sort(std::vector<Graphics*> &graphics) {
                size_t l = 0;
                size_t r = graphics.size() - 1;
                size_t i, j;
                Graphics* temp;

                for (i = l + 1; i <= r; ++i) {
                    temp = graphics[i];
                    for (j = i; j > l && isSmaller(temp, graphics[j - 1]); --j) {
                        graphics[j] = graphics[j - 1];
                    }
                    graphics[j] = temp;
                }
            }
        };

        bool IsAInFrontOfB(Graphics* a, Graphics* b);
        bool IsBInFrontOfA(Graphics* a, Graphics* b);

        /**
         * This Comparator puts Renderables with greater Z in front of Renderables with smaller Z, so that
         * Renderables far away will be rendered first.
         * This is the comparator to use for 2D applications.
         */
        typedef GraphicsSort<IsAInFrontOfB> BackToFrontGraphicsSort; // keep float as argument for compatibility

        /**
         * This Comparator puts Renderables with smaller Z in front of Renderables with greater Z,
         * meaning Renderables in front will be rendered first.
         * This is the comparator to use for 3D applications.
         */
        typedef GraphicsSort<IsBInFrontOfA> FrontToBackGraphicsSort; // keep float as argument for compatibility
    }
}

#endif //PAXENGINE3_RENDERABLESORT_H
