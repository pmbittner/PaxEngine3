//
// Created by Paul on 04.09.2018.
//

#include <iostream>

#include <paxcore/rendering/data/Asset.h>
#include <paxcore/rendering/camera/Camera.h>

namespace PAX {
    Asset::Part::Part(const std::shared_ptr<PAX::Mesh> &mesh,
                      const std::shared_ptr<PAX::Material> & material)
                      : mesh(mesh), material(material) {
        PAX_ASSERT_NOT_NULL(mesh, "Mesh can't be null!");
        //assert(material);
    }

    Asset::Part::Part(const PAX::Asset::Part &other) : Part(other.mesh, other.material) {

    }

    Asset::Asset(const std::vector<Part>& meshes, const glm::mat4 & transformation)
    : meshes(meshes),transformation(transformation)
    {

    }

    Asset::~Asset() = default;

    void Asset::addChild(const std::shared_ptr<Asset> & asset) {
        children.push_back(asset);
    }

    void Asset::render(PAX::RenderOptions &renderOptions) {
        Shader* shader = renderOptions.getShaderOptions().getShader();
        const glm::mat4 parentTransform = renderOptions.getTransformationMatrix();

        glm::mat4 worldTransform = parentTransform * transformation;
        renderOptions.setTransformationMatrix(worldTransform);
        glm::mat4 modelview = renderOptions.getViewMatrix() * worldTransform;

        // TODO: Upload projection and view as early as possible and nicht erst hier.
        //       Maybe do this in RenderOptions.
        shader->setUniform("projection", renderOptions.getProjectionMatrix(), false);
        shader->setUniform("view", renderOptions.getViewMatrix(), false);
        shader->setUniform("model", worldTransform, false);
        shader->setUniform("modelview", modelview, false);
        shader->setUniform("transposedInvModel", glm::inverse(worldTransform), true /* transpose */);


        for (Part & p : meshes) {
            bool hasMaterial = p.material.operator bool();

            if (hasMaterial)
                p.material->applyTo(renderOptions.getShaderOptions().getShader());

            p.mesh->render(renderOptions);

            if (hasMaterial)
                p.material->unapplyFrom(renderOptions.getShaderOptions().getShader());
        }
        for (auto & child : children)
            child->render(renderOptions);

        renderOptions.setTransformationMatrix(parentTransform);
    }

    void Asset::print(const std::string& indent) const {
        std::string indentpp = indent + "    ";
        std::cout << "\n" << indent << "[\n";
        for (const Part & p : meshes) {
            std::cout << indent << "Part\n";
            std::cout << indent << "[\n";
            std::cout << indentpp << "Mesh: " << p.mesh->getName() << "\n";
            std::cout << indentpp << " Mat: " << p.material->name << "\n";
            std::cout << indent << "]\n";
        }

        for (const auto& child : children) {
            std::cout << indent << "Child";
            child->print(indentpp);
        }
        std::cout << indent << "]\n";
    }

    void Asset::upload() {
        for (auto& part : meshes) {
            part.mesh->upload();
        }

        for (auto& child : children) {
            child->upload();
        }
    }

    const std::vector<std::shared_ptr<Asset>> &Asset::getChildren() const {
        return children;
    }

    const glm::mat4 &Asset::getTransformation() const {
        return transformation;
    }

    const std::vector<Asset::Part> &Asset::getMeshes() const {
        return meshes;
    }
}