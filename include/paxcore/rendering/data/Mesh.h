//
// Created by Paul on 30.06.2017.
//

#ifndef PAXENGINE3_MESH_H
#define PAXENGINE3_MESH_H

#include <unordered_map>

#include "../interface/Renderable.h"

#include <iostream>
#include <paxutil/reflection/TemplateTypeToString.h>

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

    private:
        std::string _name;
        bool _uploaded = false;
        std::vector<AttributeName> _attributeNames;

        void addAttribName(AttributeName name);

    protected:
        virtual void addAttribute(const std::vector<int> &attrib) = 0;
        virtual void addAttribute(const std::vector<float> &attrib) = 0;
        virtual void addAttribute(const std::vector<glm::vec2> &attrib) = 0;
        virtual void addAttribute(const std::vector<glm::vec3> &attrib) = 0;
        virtual void addAttribute(const std::vector<glm::vec4> &attrib) = 0;

    public:
        ~Mesh() override;

        void setName(const std::string & name);
        const std::string & getName() const;

        /// \tparam T One of float, glm::vec2, glm::vec3, glm::vec4
        /// \param attribName The name of the attribute, for example UVs
        /// \param attrib The actual attribute data
        template<typename T>
        void addAttribute(AttributeName attribName, const std::vector<T> &attrib) {
            addAttribName(attribName);
            addAttribute(attrib);
        }

        virtual bool hasAttribute(AttributeName attribName);
        virtual int getAttributeLocation(AttributeName attribName);

        virtual void upload();
        bool isUploaded();
    };
}

#endif //PAXENGINE3_MESH_H
