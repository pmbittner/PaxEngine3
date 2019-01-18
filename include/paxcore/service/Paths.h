//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_PATHS_H
#define PAXENGINE3_PATHS_H

#include <string>
#include <paxutil/macros/OSDetection.h>
#include "paxutil/io/Path.h"

namespace PAX {
    class Services;
    class Paths {
        friend Services;

    private:
        static std::string GetCurrentWorkingDirectory();

        Path _absoluteResourcePath;
        Path _workingDirectory;

        void setAbsoluteResourceDirectory(const std::string& resourceDirectory);

    public:
        Paths();
        ~Paths();

        const Path& getResourcePath() const;
        const Path& getWorkingDirectory() const;
    };
}

#endif //PAXENGINE3_PATHS_H
