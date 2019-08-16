//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_PROJECTION_H
#define PAXENGINE3_PROJECTION_H

#include <glm/glm.hpp>

namespace PAX {
    class Projection {
    private:
        bool _dirty = true;
        glm::ivec2 _resolution;

    protected:
        glm::mat4 _matrix;
        virtual void calcMatrix();
        void makeDirty();

    public:
        const glm::mat4& toMatrix();

        const glm::ivec2 & getResolution();
        void setResolution(const glm::ivec2 & res);
    };
}

#endif //PAXENGINE3_PROJECTION_H
