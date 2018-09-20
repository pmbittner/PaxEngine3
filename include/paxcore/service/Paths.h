//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_PATHS_H
#define PAXENGINE3_PATHS_H

#include <string>
#include <paxutil/macros/OSDefines.h>
#include "paxutil/io/Path.h"

namespace PAX {
    class Paths {
    private:
        std::string _relativeResourcePath = std::string("..") + Path::PathSeparator + std::string("..") + Path::PathSeparator + std::string("res") + Path::PathSeparator;
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
