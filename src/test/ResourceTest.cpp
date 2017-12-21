//
// Created by Paul on 20.12.2017.
//

#include <MainIncludes.h>
#include <test/ResourcesTest.h>

int main(int argc, char *argv[])
{
    using namespace PAX;

    Resources r;

    r.registerLoader(new PNGTextureLoader());
    r.registerLoader(new ShaderLoader());

    /// LEGAL
    {
        std::cout << "Loading \"test.png\"" << std::endl;
        std::shared_ptr<RTestTexture> testTex = r.loadOrGet<RTestTexture>("test.png");
        std::cout << testTex.get() << std::endl << std::endl;

        std::cout << "Loading \"vert.glsl\", \"frag.glsl\"" << std::endl;
        std::shared_ptr<RTestShader> testShader = r.loadOrGet<RTestShader>("vert.glsl", "frag.glsl");
        std::cout << testShader << std::endl << std::endl;
    }

    {
        std::shared_ptr<RTestShader> testShader = r.loadOrGet<RTestShader>("vert.glsl", "frag.glsl");

        std::cout << "Starting garbage collection" << std::endl;
        r.collectGarbage();
        std::cout << "done" << std::endl << std::endl;
    }

    std::cout << "Starting garbage collection" << std::endl;
    r.collectGarbage();
    std::cout << "done" << std::endl << std::endl;
}