//
// Created by Paul on 06.12.2017.
//

#include <paxcore/service/Paths.h>

#include <cstdio>  /* defines FILENAME_MAX */
#ifdef PAX_OS_WIN
    #include <direct.h>
#include <paxutil/log/Log.h>

#define PAX_GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define PAX_GetCurrentDir getcwd
#endif

namespace PAX {
    std::string Paths::GetCurrentWorkingDirectory() {
        char cCurrentPath[FILENAME_MAX];

        if (PAX_GetCurrentDir(cCurrentPath, sizeof(cCurrentPath))) {
            cCurrentPath[sizeof(cCurrentPath) - 1] = '\0'; /* not really required */
            return cCurrentPath;
        } else {
            return "Working Directory could not be obtained!";
        }
    }

    Paths::Paths() : _workingDirectory(GetCurrentWorkingDirectory())
    {
        // Initialize after _workingDirectory is initialized, as this cannot be guaranteed, if this is also placed
        // inside the initializer list.
        _absoluteResourcePath = _workingDirectory;
    }

    Paths::~Paths() = default;

    void Paths::setAbsoluteResourceDirectory(const Path & resourceDirectory) {
        PAX_LOG(PAX::Log::Level::Info, "set resource directory to " << resourceDirectory);
        _absoluteResourcePath = resourceDirectory;
    }

    const Path& Paths::getResourcePath() const {
        return _absoluteResourcePath;
    }

    const Path& Paths::getWorkingDirectory() const {
        return _workingDirectory;
    }
}

#undef PAX_GetCurrentDir