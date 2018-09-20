//
// Created by paul on 20.09.18.
//

#include <iostream>

#include <paxutil/io/Path.h>

namespace PAX {
    namespace Test {
        void PathSimplifactionTest(std::string path) {
            std::cout << "Simplify(\"" << path << "\")\n\t= \"";
            Path::simplify(path);
            std::cout << path << "\"\n\tis" << (Path(path).isAbsolute() ? "absolute" : "relative") << "\n" << std::endl;

        }
    }
}

int main(int argc, char** args) {
    using namespace PAX;

    { // Test Path class
        Test::PathSimplifactionTest("");
        Test::PathSimplifactionTest(".");
        Test::PathSimplifactionTest("/.");

        Test::PathSimplifactionTest("/absolute/path/to/file.txt");
        Test::PathSimplifactionTest("/absolute/path/to/dir");
        Test::PathSimplifactionTest("/absolute/up/../and/down.txt");
        Test::PathSimplifactionTest("/absolute/stay/./here.txt");

        Test::PathSimplifactionTest("relative/path/to/file.txt");
        Test::PathSimplifactionTest("relative/path/to/dir");
        Test::PathSimplifactionTest("relative/up/../and/down.txt");
        Test::PathSimplifactionTest("relative/stay/./here.txt");

        Test::PathSimplifactionTest("../down/libsomelib.a");
        Test::PathSimplifactionTest("../down/../down2/libsomelib.a");
        Test::PathSimplifactionTest("./down/libsomelib.a");
        Test::PathSimplifactionTest("./down/./down/libsomelib.a");
    }

    { // Test Paths class

    }
}