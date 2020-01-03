//
// Created by Paul on 06.12.2017.
//

#ifndef PAXENGINE3_PATHS_H
#define PAXENGINE3_PATHS_H

#include <string>
#include <polypropylene/definitions/OSDetection.h>
#include "polypropylene/io/Path.h"

namespace PAX {
    class Services;
    class Paths {
        friend Services;

    private:
        static std::string GetCurrentWorkingDirectory();

        Path _absoluteResourcePath;
        Path _workingDirectory;

        void setAbsoluteResourceDirectory(const Path& resourceDirectory);

    public:
        Paths();
        ~Paths();

        PAX_NODISCARD const Path& getResourcePath() const;
        PAX_NODISCARD const Path& getWorkingDirectory() const;
    };
}

#endif //PAXENGINE3_PATHS_H
