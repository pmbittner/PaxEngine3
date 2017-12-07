//
// Created by Paul on 06.12.2017.
//

#include <core/service/Paths.h>

namespace PAX {
    Paths::~Paths() {

    }

    void Paths::setExecutionDirectory(const std::string& executionDirectory) {
        _executionDirectory = executionDirectory;
        _absoluteResourcePath = _executionDirectory + _relativeResourcePath;
    }

    const std::string& Paths::RelativeResourcePath() {
        return _relativeResourcePath;
    }

    const std::string& Paths::AbsoluteResourcePath() {
        return _absoluteResourcePath;
    }

    const std::string& Paths::ExecutionDirectory() {
        return _executionDirectory;
    }
}