 //
// Created by Paul on 28.04.2017.
//

#ifndef PAXENGINE3_GENERICTEST_H
#define PAXENGINE3_GENERICTEST_H

namespace TEMPLATE_TRIAL {
    class IResource {
    public:
        std::string path;
        virtual std::string name() = 0;
    };

    class Shader : public IResource {
    public:
        virtual std::string name() override {
            return std::string("Shader ") + path;
        }
    };

    class Texture : public IResource {
    public:
        virtual std::string name() override {
            return std::string("Texture ") + path;
        }
    };


    class ResourceManager {
    public:
        template<typename RESTYPE>
        RESTYPE *loadResource(std::string path) {
            RESTYPE *res = new RESTYPE;
            res->path = path;
            return res;
        }
    };

    bool genericTest() {
        ResourceManager resmng;
        Shader *shader = resmng.loadResource<Shader>("shader.txt");
        Texture *texture = resmng.loadResource<Texture>("texture.png");

        std::cout << " Shader res: " << shader->name() << std::endl;
        std::cout << "Texture res: " << texture->name() << std::endl;
    }
}

#endif //PAXENGINE3_GENERICTEST_H
