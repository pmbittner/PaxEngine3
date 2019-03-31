//
// Created by Paul on 30.08.2018.
//

#include <vector>

#include <paxutil/io/FileTypeChecker.h>
#include <paxcore/service/Services.h>
#include <paxcore/rendering/data/Material.h>

#include "paxassimp/AssimpResourceLoader.h"

/// assimp
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <paxcore/rendering/factory/MeshFactory.h>

namespace PAX {
    namespace AssetImport {
        struct ImportData {
            std::unordered_map<aiMesh*, std::shared_ptr<Mesh>> _meshes;
            std::unordered_map<aiMaterial*, std::shared_ptr<Material>> _materials;
            Path _path;

            explicit ImportData(const Path & path) : _path(path) {}
        };

        static void aiVector3DVectorToGlmVec3Vector(aiVector3D* aivec, std::vector<glm::vec3> & glmvec) {
            for (unsigned int i = 0; i < glmvec.size(); ++i) {
                aiVector3D aivalue = aivec[i];
                glmvec[i] = glm::vec3(aivalue.x, aivalue.y, aivalue.z);
            }
        }

        static void aiVector3DVectorToGlmVec2Vector(aiVector3D* aivec, std::vector<glm::vec2> & glmvec) {
            for (unsigned int i = 0; i < glmvec.size(); ++i) {
                aiVector3D aivalue = aivec[i];
                glmvec[i] = glm::vec2(aivalue.x, aivalue.y);
            }
        }

        static glm::mat4 aiMatrix4x4ToGlmMat4(const aiMatrix4x4 & aimat)  {
            return glm::mat4(
                // These are the four columns
                glm::vec4(aimat.a1, aimat.b1, aimat.c1, aimat.d1),
                glm::vec4(aimat.a2, aimat.b2, aimat.c2, aimat.d2),
                glm::vec4(aimat.a3, aimat.b3, aimat.c3, aimat.d3),
                glm::vec4(aimat.a4, aimat.b4, aimat.c4, aimat.d4)
            );
        }

        static glm::vec3 aiColor3DToGlmVec3(const aiColor3D & color) {
            return {color.r, color.g, color.b};
        }

        static Texture::WrapMode getTextureWrapMode(aiMaterial* aimaterial, bool horizontal, long aiTextureType = aiTextureType_DIFFUSE) {
            Texture::WrapMode wrapMode = Texture::WrapMode::Repeat;
            int aiWrapMode;
            aiReturn aiWrapReturn;
            if (horizontal) {
                aiWrapReturn = aimaterial->Get(AI_MATKEY_MAPPINGMODE_U(aiTextureType, 0), aiWrapMode);
            } else {
                aiWrapReturn = aimaterial->Get(AI_MATKEY_MAPPINGMODE_V(aiTextureType, 0), aiWrapMode);
            }

            if (aiWrapReturn == aiReturn_SUCCESS) {
                switch (aiWrapMode) {
                    case aiTextureMapMode_Clamp: {
                        wrapMode = Texture::WrapMode::ClampToEdge;
                        break;
                    }

                    case aiTextureMapMode_Mirror: {
                        wrapMode = Texture::WrapMode::MirrorRepeat;
                        break;
                    }

                    case aiTextureMapMode_Decal: {
                        wrapMode = Texture::WrapMode::ClampToBorder;
                        break;
                    }

                        // aiTextureMapMode_Wrap
                    default: break;
                }
            }

            return wrapMode;
        }

        static std::shared_ptr<Mesh> aiMeshToPaxMesh(aiMesh* assimpMesh, ImportData & importData) {
            std::vector<glm::vec3> vertices(assimpMesh->mNumVertices);
            std::vector<glm::ivec3> faces;

            // vertices and faces are guaranteed to be set in assimpMesh
            aiVector3DVectorToGlmVec3Vector(assimpMesh->mVertices, vertices);

            for (unsigned int f = 0; f < assimpMesh->mNumFaces; ++f) {
                aiFace aiface = assimpMesh->mFaces[f];
                // We always let assimp triangulate
                assert(aiface.mNumIndices == 3);
                faces.emplace_back(
                        glm::ivec3(aiface.mIndices[0], aiface.mIndices[1], aiface.mIndices[2])
                        );
            }

            std::shared_ptr<Mesh> paxmesh = Services::GetFactoryService().get<MeshFactory>()->create(vertices, faces);
            paxmesh->setName(assimpMesh->mName.C_Str());

            if (assimpMesh->HasNormals()) {
                std::vector<glm::vec3> normals(assimpMesh->mNumVertices);
                aiVector3DVectorToGlmVec3Vector(assimpMesh->mNormals, normals);
                paxmesh->addAttribute(Mesh::Normals, normals);
            }

            // A single mesh may containt multiple channels for UVs. For now we only support the first one,
            if (assimpMesh->HasTextureCoords(0)) {
                std::vector<glm::vec2> uvs(assimpMesh->mNumVertices);
                aiVector3DVectorToGlmVec2Vector(assimpMesh->mTextureCoords[0], uvs);
                paxmesh->addAttribute(Mesh::UVs, uvs);
            }

            // TODO: TANGENT and BITANGENT

            return paxmesh;
        }

        static std::shared_ptr<Material> aiMaterialToPaxMaterial(aiMaterial* aimaterial, ImportData & importData) {
            std::shared_ptr<Material> paxmaterial = std::make_shared<Material>(aimaterial->GetName().C_Str());

            { // Diffuse color
                aiColor3D color;
                aiReturn ret = aimaterial->Get(AI_MATKEY_COLOR_DIFFUSE, color);

                if (ret == aiReturn_SUCCESS) {
                    paxmaterial->diffuse.color = aiColor3DToGlmVec3(color);
                }
            }
            { // Specular color
                aiColor3D color;
                aiReturn ret = aimaterial->Get(AI_MATKEY_COLOR_SPECULAR, color);

                if (ret == aiReturn_SUCCESS) {
                    paxmaterial->specular.color = aiColor3DToGlmVec3(color);
                }
            }
            { // Ambient color
                aiColor3D color;
                aiReturn ret = aimaterial->Get(AI_MATKEY_COLOR_AMBIENT, color);

                if (ret == aiReturn_SUCCESS) {
                    paxmaterial->ambient.color = aiColor3DToGlmVec3(color);
                }
            }

            { // Specular exponent / shininess
                float shininess;
                aiReturn ret = aimaterial->Get(AI_MATKEY_SHININESS, shininess);

                if (ret == aiReturn_SUCCESS) {
                    paxmaterial->specular.exponent = shininess;
                }
            }

            { // Opacity
                float opacity;
                aiReturn ret = aimaterial->Get(AI_MATKEY_OPACITY, opacity);

                if (ret == aiReturn_SUCCESS) {
                    paxmaterial->opacity = opacity;
                }
            }

            { // Diffuse texture
                aiString texPath;
                aiReturn ret = aimaterial->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), texPath);

                if (ret == aiReturn_SUCCESS) {
                    Path dir = importData._path.getDirectory();
                    Path pathToTex = dir + std::string(texPath.C_Str());
                    paxmaterial->diffuse.texture = Services::GetResources().load<Texture>(pathToTex);

                    if (paxmaterial->diffuse.texture) {
                        Texture::WrapMode wrapS = getTextureWrapMode(aimaterial, true);
                        Texture::WrapMode wrapT = getTextureWrapMode(aimaterial, false);

                        paxmaterial->diffuse.texture->setWrapMode(wrapS, wrapT);
                    }
                }
            }

            return paxmaterial;
        }

        static std::shared_ptr<Asset> aiNodeToAsset(const aiScene* scene, aiNode* node, ImportData& importData) {
            std::vector<Asset::Part> assetParts;

            for (unsigned int i = 0; i < node->mNumMeshes; ++i) {
                aiMesh* aimesh = scene->mMeshes[node->mMeshes[i]];
                aiMaterial* aimaterial = scene->mMaterials[aimesh->mMaterialIndex];
                assetParts.emplace_back(Asset::Part(
                        importData._meshes.at(aimesh),
                        importData._materials.at(aimaterial)
                ));
            }

            glm::mat4 transformation = aiMatrix4x4ToGlmMat4(node->mTransformation);
            return std::make_shared<Asset>(assetParts, transformation);
        }

        static std::shared_ptr<Asset> traverseAiTree(const aiScene* scene, aiNode* node, ImportData& importData) {
            std::shared_ptr<Asset> asset = aiNodeToAsset(scene, node, importData);

            for (unsigned int i = 0; i < node->mNumChildren; ++i)
                asset->addChild(traverseAiTree(scene, node->mChildren[i], importData));

            return asset;
        }

        bool AssimpResourceLoader::canLoad(Path p) const {
            static Util::FileTypeChecker formatChecker({
                "obj"
            });
            return formatChecker.check(p);
        }

        std::shared_ptr<Asset> AssimpResourceLoader::load(Path p) {
            PAX_assertNotNull(Services::GetFactoryService().get<MeshFactory>(), "[AssimpResourceLoader::load] MeshFactory is required, but is not registered!")

            Assimp::Importer importer;

            // TODO: Find optimal default value and make this configurable
            // FIXME: FlipUVs may only be necessary for some assets (see TODO ^^)
            // Hint aiProcess_MakeLeftHanded is needed for DirectX
            // IMPORTANT: Always pass aiProcess_Triangulate
            unsigned int postProcessingFlags = aiProcessPreset_TargetRealtime_Fast | aiProcess_Triangulate | aiProcess_FlipUVs;
            const aiScene* scene = importer.ReadFile(p.toString(), postProcessingFlags);

            if (!scene) {
                // Import failed
                std::stringstream errorStream;
                errorStream << "[PAX::AssetImport::AssimpResourceLoader::load] Import failed: " << importer.GetErrorString();

                std::cerr << errorStream.str() << std::endl;
                throw std::runtime_error(errorStream.str());
            }

            // empty scene do not make any sense for us
            if (scene->HasMeshes()) {
                ImportData importData(p);

                // preload meshes to avoid duplicate instanciation
                for (unsigned int i = 0; i < scene->mNumMeshes; ++i) {
                    aiMesh* m = scene->mMeshes[i];
                    importData._meshes[m] = aiMeshToPaxMesh(m, importData);
                }
                // preload materials
                for (unsigned int i = 0; i < scene->mNumMaterials; ++i) {
                    aiMaterial* m = scene->mMaterials[i];
                    importData._materials[m] = aiMaterialToPaxMaterial(m, importData);
                }

                std::shared_ptr<Asset> shared_asset = traverseAiTree(scene, scene->mRootNode, importData);

                // upload all meshes
                for (auto & mesh : importData._meshes) {
                    mesh.second->upload();
                }

                return shared_asset;
            }

            return nullptr;
        }

        std::shared_ptr<Asset> AssimpResourceLoader::loadToOrGetFromResources(PAX::Resources &resources,
                                                                              const PAX::VariableHierarchy &parameters) {
            return loadFromPath("AssimpResourceLoader", resources, parameters);
        }
    }
}