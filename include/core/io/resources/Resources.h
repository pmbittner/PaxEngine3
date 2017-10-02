//
// Created by Paul on 18.09.2017.
//

#ifndef PAXENGINE3_RESOURCES_H
#define PAXENGINE3_RESOURCES_H

#include "utility/TypeMap.h"
#include "utility/StringUtils.h"
#include <string>
#include <vector>
#include <iostream>
#include <memory>

namespace PAX {
    class RTestTexture {};
    class RTestShader {};

    class IResourceLoader {
    public:
        virtual ~IResourceLoader() {}
    };

    template<typename Resource, typename... Params>
    class ResourceLoader : public IResourceLoader {
    public:
        virtual bool canLoad(Params...) = 0;
        virtual Resource* load(Params...) = 0;
    };

    class PNGTextureLoader : public ResourceLoader<RTestTexture, const char*> {
    public:
        virtual bool canLoad(const char* path) override {
            std::string extension = Util::getExtension(path);
            return extension == "png" || extension == "PNG";
        }

        RTestTexture* load(const char* path) override {
            std::cout << "PNGTextureLoader loads " << path << std::endl;
            return new RTestTexture();
        }
    };

    class ShaderLoader : public ResourceLoader<RTestShader, const char*, const char*> {
    public:
        virtual bool canLoad(const char* vertexShaderPath, const char* fragmentShaderPath) override {
            return true;
        }

        RTestShader* load(const char* vertexShaderPath, const char* fragmentShaderPath) {
            std::cout << "ShaderLoader loads " << vertexShaderPath << ", " << fragmentShaderPath << std::endl;
            return new RTestShader();
        }
    };

    struct ISignature {
        virtual bool equals(ISignature* signature) = 0;
        virtual bool equals(ISignature& signature) {
            return equals(&signature);
        }
    };

    template<typename... S>
    struct Signature : public ISignature {
        std::tuple<S...> values;

        bool equals(Signature<S...> const& rhs) const {
            return values == rhs.values;
        }

        bool equals(S const&... rhs) const {
            // forward here to produce a tuple<S const&...> and avoid an unnecessary copy
            return values == std::forward_as_tuple(rhs...);
        }

        virtual bool equals(ISignature* signature) override {
            Signature<S...>* concreteSignature = dynamic_cast<Signature<S...>*>(signature);
            if (concreteSignature) {
                return equals(concreteSignature);
            }
            return false;
        }
    };

    class Resources;
    class ResourceHandle {
        friend class Resources;
        //union {
        //    const int _id = 0;
            void* _resource = nullptr;
        //};
        size_t _resourceSize = 0;
        int _uses = 0;

        ISignature *_signature;

    public:
        ResourceHandle() {

        }

        ~ResourceHandle() {
            delete _signature;
        }
    };

    class Resources {
        TypeMap<std::vector<IResourceLoader*>> _loaders;
        TypeMap<std::vector<ResourceHandle>> _resourcesInUse;

    private:
        template<typename Resource, typename... Params>
        void registerResource(Resource *res) {
            Signature<Params...> s;

            std::vector<ResourceHandle> &handles = _resourcesInUse.get<Resource>();
            for (ResourceHandle &handle : handles) {
                if (s.equals(handle._signature)) {
                    handle._uses++;
                    return;
                }
            }

            ResourceHandle newEntry;
            newEntry._signature = new Signature<Params...>();
            newEntry._uses = 1;
            newEntry._resource = res;
            newEntry._resourceSize = sizeof(Resource);
            handles.push_back(newEntry);
        }

    public:

        template<typename Resource, typename... Params>
        bool registerLoader(ResourceLoader<Resource, Params...>* loader) {
            std::vector<IResourceLoader*> &loaders = _loaders.get<Resource>();
            loaders.push_back(loader);
        }

        template<typename Resource, typename... Params>
        Resource* loadOrGet(Params... p) {

        }

        template<typename Resource, typename... Params>
        Resource* load(Params... p) {
            std::vector<IResourceLoader*> &possibleLoaders = _loaders.get<Resource>();
            for (IResourceLoader *possibleLoader : possibleLoaders) {
                ResourceLoader<Resource, Params...>* loader = dynamic_cast<ResourceLoader<Resource, Params...>*>(possibleLoader);
                if (loader) {
                    if (loader->canLoad(p...)) {
                        Resource *r = loader->load(p...);
                        registerResource<Resource, Params...>(r);
                        return r;
                    }
                }
            }

            return nullptr;
        }
    };

    void ResourcesTest() {
        Resources r;

        r.registerLoader(new PNGTextureLoader());
        r.registerLoader(new ShaderLoader());

        /// LEGAL
        std::cout << "Loading \"test.png\"" << std::endl;
        RTestTexture *testTex = r.load<RTestTexture>("test.png");
        std::cout << testTex << std::endl << std::endl;

        std::cout << "Loading \"vert.glsl\", \"frag.glsl\"" << std::endl;
        std::cout << r.load<RTestShader>("vert.glsl", "frag.glsl") << std::endl << std::endl;

        /// FAILS
        std::cout << "Loading \"test.lol\"" << std::endl;
        std::cout << r.load<RTestTexture>("test.lol") << std::endl << std::endl;

        std::cout << "Loading \"vert.glsl\", \"frag.glsl\", \"some.shit\"" << std::endl;
        std::cout << r.load<RTestShader>("vert.glsl", "frag.glsl", "some.shit") << std::endl << std::endl;
    }
}

#endif //PAXENGINE3_RESOURCES_H
