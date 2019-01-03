//
// Created by Paul on 04.09.2018.
//

#include <iostream>

#include <paxcore/rendering/data/Asset.h>
#include <paxcore/rendering/camera/Camera.h>

namespace PAX {
    Asset::Part::Part(const std::shared_ptr<PAX::Mesh> &mesh,
                      const std::shared_ptr<PAX::Material> & material)
                      : _mesh(mesh), _material(material) {
        assert(mesh);
        assert(material);
    }

    Asset::Part::Part(const PAX::Asset::Part &other) : Part(other._mesh, other._material) {

    }

    Asset::Asset(const std::vector<Part>& meshes, const glm::mat4 & transformation)
    : _meshes(meshes),_transformation(transformation)
    {

    }

    Asset::~Asset() {
        std::cout << "[Asset::~Asset] ------------------------------------------------------------------------------" << std::endl;
    }

    void Asset::addChild(const std::shared_ptr<Asset> & asset) {
        _children.push_back(asset);
    }

    void Asset::render(PAX::RenderOptions &renderOptions) {
        Shader* shader = renderOptions.getShaderOptions().getShader();
        const glm::mat4 parentTransform = renderOptions.getTransformationMatrix();

        glm::mat4 worldTransform = parentTransform * _transformation;
        renderOptions.setTransformationMatrix(worldTransform);
        glm::mat4 modelview = renderOptions.getViewMatrix() * worldTransform;

        // TODO: Upload projection and view as early as possible and nicht erst hier.
        shader->setUniform("projection", renderOptions.getProjectionMatrix(), false);
        shader->setUniform("view", renderOptions.getViewMatrix(), false);
        shader->setUniform("model", worldTransform, false);
        shader->setUniform("modelview", modelview, false);
        shader->setUniform("transposedInvModel", glm::inverse(worldTransform), true /* transpose */);

        for (Part & p : _meshes) {
            p._material->applyTo(renderOptions.getShaderOptions().getShader());
            p._mesh->render(renderOptions);
        }
        for (auto & child : _children)
            child->render(renderOptions);

        renderOptions.setTransformationMatrix(parentTransform);
    }

    void Asset::print(const std::string& indent) const {
        std::string indentpp = indent + "    ";
        std::cout << "\n" << indent << "[\n";
        for (const Part & p : _meshes) {
            std::cout << indent << "Part\n";
            std::cout << indent << "[\n";
            std::cout << indentpp << "Mesh: " << p._mesh->getName() << "\n";
            std::cout << indentpp << " Mat: " << p._material->name << "\n";
            std::cout << indent << "]\n";
        }

        for (const auto& child : _children) {
            std::cout << indent << "Child";
            child->print(indentpp);
        }
        std::cout << indent << "]\n";
    }
}