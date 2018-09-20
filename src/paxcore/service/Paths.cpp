//
// Created by Paul on 06.12.2017.
//

#include <paxcore/service/Paths.h>

#include <cstdio>  /* defines FILENAME_MAX */
#ifdef PAX_OS_WIN
    #include <direct.h>
    #define PAX_GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define PAX_GetCurrentDir getcwd
#endif

namespace PAX {
    Paths::Paths() {
        char cCurrentPath[FILENAME_MAX];

        if (PAX_GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
            cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
            _workingDirectory = std::string(cCurrentPath);
        } else {
            _workingDirectory = "Working Directory could not be obtained!";
        }


    }

    Paths::~Paths() = default;

    void Paths::setExecutionDirectory(const std::string& executionDirectory) {
        _executionDirectory = executionDirectory;
        _absoluteResourcePath = _executionDirectory + _relativeResourcePath;
    }

    const std::string& Paths::getRelativeResourcePath() const {
        return _relativeResourcePath;
    }

    const std::string& Paths::getAbsoluteResourcePath() const {
        return _absoluteResourcePath;
    }

    const std::string& Paths::getExecutionDirectory() const {
        return _executionDirectory;
    }

    const std::string& Paths::getWorkingDirectory() const {
        return _workingDirectory;
    }
}

#undef PAX_GetCurrentDir