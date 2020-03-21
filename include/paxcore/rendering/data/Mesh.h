//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_MESH_H
#define PAXENGINE3_MESH_H

#include <unordered_map>

#include "../interface/Renderable.h"

#include <iostream>
#include <polypropylene/reflection/TemplateTypeToString.h>

namespace PAX {
    class Mesh : public Renderable {
    public:
        using AttributeName = int;

        static const AttributeName Unspecified; // -1
        static const AttributeName Vertices; // 0
        static const AttributeName Normals; // 1
        static const AttributeName UVs; // 2
        static const AttributeName Tangents; // 3
        static const AttributeName Bitangents; // 4

        enum class FaceMode {
            Triangles,
            Lines,
            Points
        };

    private:
        std::string name = "Unnamed";
        bool uploaded = false;
        FaceMode facemode = FaceMode::Triangles;

    public:
        ~Mesh() override;

        void setName(const std::string & name);
        PAX_NODISCARD const std::string & getName() const;

        virtual void addAttribute(AttributeName name, const std::vector<int> &attrib) = 0;
        virtual void addAttribute(AttributeName name, const std::vector<float> &attrib) = 0;
        virtual void addAttribute(AttributeName name, const std::vector<glm::vec2> &attrib) = 0;
        virtual void addAttribute(AttributeName name, const std::vector<glm::vec3> &attrib) = 0;
        virtual void addAttribute(AttributeName name, const std::vector<glm::vec4> &attrib) = 0;

        virtual void updateAttribute(AttributeName name, const std::vector<int> &attrib) = 0;
        virtual void updateAttribute(AttributeName name, const std::vector<float> &attrib) = 0;
        virtual void updateAttribute(AttributeName name, const std::vector<glm::vec2> &attrib) = 0;
        virtual void updateAttribute(AttributeName name, const std::vector<glm::vec3> &attrib) = 0;
        virtual void updateAttribute(AttributeName name, const std::vector<glm::vec4> &attrib) = 0;

        virtual bool hasAttribute(AttributeName attribName) = 0;
        virtual int getAttributeLocation(AttributeName attribName) = 0;

        virtual void setFaceMode(FaceMode facemode);
        PAX_NODISCARD FaceMode getFaceMode() const;

        virtual void upload();
        PAX_NODISCARD bool isUploaded() const;
    };
}

#endif //PAXENGINE3_MESH_H
