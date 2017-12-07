//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_PATHS_H
#define PAXENGINE3_PATHS_H

#include <string>
#include <utility/macros/OSDefines.h>

namespace PAX {
    class Paths {
    public:
        static constexpr char PathSeparator =
#ifdef PAX_OS_WIN
        '\\';
#else
        '/';
#endif

    private:
        std::string _relativeResourcePath = std::string("..") + PathSeparator + std::string("..") + PathSeparator + std::string("res") + PathSeparator;
        std::string _absoluteResourcePath;
        std::string _executionDirectory;

    public:
        ~Paths();

        void setExecutionDirectory(const std::string& executionDirectory);

        const std::string& RelativeResourcePath();
        const std::string& AbsoluteResourcePath();
        const std::string& ExecutionDirectory();
    };
}

#endif //PAXENGINE3_PATHS_H
