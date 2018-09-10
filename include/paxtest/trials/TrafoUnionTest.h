//
// Created by Paul on 17.04.2017.
//

#ifndef PAXENGINE3_TRAFOUNIONTEST_H
#define PAXENGINE3_TRAFOUNIONTEST_H

namespace UnionTest {
    struct Vector2 { float x, y; };
    struct Vector3 { float x, y, z; };

    struct TrafoUnionTest {
        union {
            Vector2 pos2D;
            Vector3 pos3D;
        };
        Vector3 rot;

        Vector2* getPos2D() {
            return &pos2D;
        }

        Vector3* getPos3D() {
            return &pos3D;
        }

        float* getRotation2D() {
             return &rot.z;
        }

        Vector3* getRotation3D() {
            return &rot;
        }
    };
}
#endif //PAXENGINE3_TRAFOUNIONTEST_H
