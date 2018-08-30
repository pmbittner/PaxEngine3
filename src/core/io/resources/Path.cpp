//
// Created by Paul on 06.01.2018.
//

#include <core/io/resources/Path.h>
#include <iostream>

namespace PAX {
    Path::Path(const std::string& path) : _path(path) {
#ifdef PAX_OS_WIN
            Util::str_replace(_path, Paths::PathSeparator_Unix, Paths::PathSeparator);
#else
            Util::str_replace(_path, Paths::PathSeparator_Win, Paths::PathSeparator);
#endif
    }

    Path::Path(const char *path) : Path(std::string(path)) {

    }

    bool Path::operator==(const Path &other) const {
        return _path.compare(other._path) == 0;
    }

    Path::operator const char*() const {
        return _path.c_str();
    }

    Path::operator std::string() const {
        return _path;
    }

    const std::string& Path::toString() const {
        return _path;
    }
}