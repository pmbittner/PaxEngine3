//
// Created by Paul on 06.12.2017.
//

#include <paxcore/service/Paths.h>
#include <polypropylene/log/Log.h>

#include <cstdio>  /* defines FILENAME_MAX */
#ifdef PAX_OS_WIN
    #include <direct.h>
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

    Paths::Paths() : workingDirectory(GetCurrentWorkingDirectory())
    {
        // Initialize after workingDirectory is initialized, as this cannot be guaranteed, if this is also placed
        // inside the initializer list.
        absoluteEngineResourceDirectory = workingDirectory;
        absoluteCustomResourceDirectory = workingDirectory;
    }

    Paths::~Paths() = default;

    void Paths::setEngineResourceDirectory(const Path & engineResourceDirectory) {
        absoluteEngineResourceDirectory = engineResourceDirectory.toAbsolute();
        PAX_LOG(PAX::Log::Level::Info, "Set engine's resource directory to " << absoluteEngineResourceDirectory);
    }

    void Paths::setCustomResourceDirectory(const Path & customResourceDirectory) {
        absoluteCustomResourceDirectory = customResourceDirectory.toAbsolute();
        PAX_LOG(PAX::Log::Level::Info, "Set custom resource directory to " << absoluteCustomResourceDirectory);
    }

    const Path& Paths::getEngineResourceDirectory() const {
        return absoluteEngineResourceDirectory;
    }

    const Path& Paths::getCustomResourceDirectory() const {
        return absoluteCustomResourceDirectory;
    }

    const Path& Paths::getWorkingDirectory() const {
        return workingDirectory;
    }
}

#undef PAX_GetCurrentDir