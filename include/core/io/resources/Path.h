//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PATH_H
#define PAXENGINE3_PATH_H

#include <string>
#include <core/service/Paths.h>
#include <utility/StringUtils.h>

namespace PAX {
    class Path {
        std::string _path;

    public:
        Path(const std::string& path);
        Path(const char* path);

        bool operator==(const Path& other) const;
        operator const char*() const;
        operator std::string() const;

        const std::string& toString() const;
    };
}

std::ostream& operator<<(std::ostream& os, const PAX::Path & p);

#endif //PAXENGINE3_PATH_H
