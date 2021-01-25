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

        Path absoluteEngineResourceDirectory;
        Path absoluteCustomResourceDirectory;
        Path workingDirectory;

        void setEngineResourceDirectory(const Path& engineResourceDirectory);
        void setCustomResourceDirectory(const Path& customResourceDirectory);

    public:
        Paths();
        ~Paths();

        PAX_NODISCARD const Path& getEngineResourceDirectory() const;
        PAX_NODISCARD const Path& getCustomResourceDirectory() const;
        PAX_NODISCARD const Path& getWorkingDirectory() const;
    };
}

#endif //PAXENGINE3_PATHS_H
