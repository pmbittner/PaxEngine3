//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_MESH_H
#define PAXENGINE3_MESH_H

#include "../interface/Renderable.h"

namespace PAX {
    class Mesh : public Renderable {
    public:
        virtual void addAttribute(std::vector<float> &attrib) = 0;
        virtual void addAttribute(std::vector<glm::vec2> &attrib) = 0;
        virtual void addAttribute(std::vector<glm::vec3> &attrib) = 0;
        virtual void addAttribute(std::vector<glm::vec4> &attrib) = 0;

        virtual void finalize() = 0;
        virtual void upload() = 0;

        virtual void destroy() = 0;
    };
}

#endif //PAXENGINE3_MESH_H
