//
// Created by Paul on 28.05.2017.
//

#ifndef PAXENGINE3_SCENEGRAPHTEST_H
#define PAXENGINE3_SCENEGRAPHTEST_H

#include "../core/world/World.h"

namespace PAX {
    namespace TEST {
        namespace SCENEGRAPH {

            class TestGraphics: public Graphics {

            };

            int test() {
                World w;
                WorldLayer *mainLayer = w.getMainLayer();

                Entity e;
                e.add<TestGraphics>(new TestGraphics);

                mainLayer->spawn(&e);

                mainLayer->getSceneGraph()->prettyPrint();

                return 1;
            }
        }
    }
}

#endif //PAXENGINE3_SCENEGRAPHTEST_H
