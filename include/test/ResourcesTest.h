//
// Created by Paul on 03.10.2017.
//

#ifndef PAXENGINE3_RESOURCESTEST_H
#define PAXENGINE3_RESOURCESTEST_H

#include <iostream>
#include <core/io/resources/Resources.h>
#include <utility/StringUtils.h>

namespace PAX {
    class RTestTexture {};
    class RTestShader {};

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

        virtual bool free(RTestTexture* res) override {
            std::cout << "PNGTextureLoader frees " << res << std::endl;
            delete res;
        };
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

        virtual bool free(RTestShader* res) override {
            std::cout << "ShaderLoader frees " << res << std::endl;
            delete res;
        };
    };

    void ResourcesTest() {
        Resources r;

        r.registerLoader(new PNGTextureLoader());
        r.registerLoader(new ShaderLoader());

        /// LEGAL
        std::cout << "Loading \"test.png\"" << std::endl;
        RTestTexture *testTex = r.loadOrGet<RTestTexture>("test.png");
        std::cout << testTex << std::endl << std::endl;

        std::cout << "Loading \"vert.glsl\", \"frag.glsl\"" << std::endl;
        RTestShader *testShader = r.loadOrGet<RTestShader>("vert.glsl", "frag.glsl");
        std::cout << testShader << std::endl << std::endl;

        /// FAILS
        std::cout << "Loading \"test.lol\"" << std::endl;
        std::cout << r.loadOrGet<RTestTexture>("test.lol") << std::endl << std::endl;

        std::cout << "Loading \"vert.glsl\", \"frag.glsl\", \"some.shit\"" << std::endl;
        std::cout << r.loadOrGet<RTestShader>("vert.glsl", "frag.glsl", "some.shit") << std::endl << std::endl;

        /// FREES
        std::cout << "Freeing something unregistered" << std::endl;
        RTestTexture s;
        std::cout << r.free(&s) << std::endl;

        std::cout << "Freeing \"test.png\"" << std::endl;
        std::cout << r.free(testTex) << std::endl;

        std::cout << "Freeing \"test.png\" again!" << std::endl;
        std::cout << r.free(testTex) << std::endl;

        std::cout << "Freeing \"vert.glsl\", \"frag.glsl\"" << std::endl;
        std::cout << r.free(testShader) << std::endl;
    }
}

#endif //PAXENGINE3_RESOURCESTEST_H
