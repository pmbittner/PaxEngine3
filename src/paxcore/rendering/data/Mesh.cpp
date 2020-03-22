//
// Created by Paul on 04.09.2018.
//

#include <paxcore/rendering/data/Mesh.h>
#include <polypropylene/stdutils/CollectionUtils.h>

#include <iostream>

namespace PAX {
    Mesh::~Mesh() = default;

    void Mesh::setName(const std::string &name) {
        this->name = name;
    }

    const std::string& Mesh::getName() const {
        return name;
    }

    void Mesh::upload() {
        uploaded = true;
    }

    bool Mesh::isUploaded() const {
        return uploaded;
    }

    void Mesh::setFaceMode(PAX::Mesh::FaceMode facemode) {
        this->facemode = facemode;
    }

    Mesh::FaceMode Mesh::getFaceMode() const {
        return facemode;
    }
}