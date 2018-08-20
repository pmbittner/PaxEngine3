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
        static constexpr char PathSeparator_Win = '\\';
        static constexpr char PathSeparator_Unix = '/';
        static constexpr char PathSeparator =
#ifdef PAX_OS_WIN
                PathSeparator_Win;
#else
        PathSeparator_Unix;
#endif

    private:
        std::string _relativeResourcePath = std::string("..") + PathSeparator + std::string("..") + PathSeparator + std::string("res") + PathSeparator;
        std::string _absoluteResourcePath;
        std::string _executionDirectory;
        std::string _workingDirectory;

    public:
        Paths();
        ~Paths();

        void setExecutionDirectory(const std::string& executionDirectory);

        const std::string& getRelativeResourcePath() const;
        const std::string& getAbsoluteResourcePath() const;
        const std::string& getExecutionDirectory() const;
        const std::string& getWorkingDirectory() const;
    };
}

#endif //PAXENGINE3_PATHS_H
