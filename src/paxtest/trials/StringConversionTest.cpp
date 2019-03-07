//
// Created by Bittner on 06.03.2019.
//

#include <iostream>
#include <paxutil/lib/GlmIncludes.h>
#include <paxutil/StringUtils.h>

int main(int argc, char* argv[]) {
    std::cout << "Moinsen zum Test" << std::endl;

    using namespace PAX::Util::String;

#define PAX_STRCONVTEST(type, str) std::cout << "tryParse(" << str << ") = " << tryParse<type>(str) << std::endl;

    PAX_STRCONVTEST(int, "1")
    PAX_STRCONVTEST(bool, "true")
    PAX_STRCONVTEST(glm::ivec2, "[1, 2]")
    PAX_STRCONVTEST(glm::vec3, "[1, 2, 3]")

    return 0;
}