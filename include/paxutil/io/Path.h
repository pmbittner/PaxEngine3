//
// Created by Paul on 06.01.2018.
//

#ifndef PAXENGINE3_PATH_H
#define PAXENGINE3_PATH_H

#include <string>
#include <paxutil/StringUtils.h>
#include <paxutil/macros/OSDefines.h>

namespace PAX {
    class Path {
    public:
        static constexpr char PathSeparator_Win = '\\';
        static constexpr char PathSeparator_Unix = '/';
        static constexpr char PathSeparator =
#ifdef PAX_OS_WIN
                PathSeparator_Win;
#else
                PathSeparator_Unix;
#endif

        static bool isAbsolute(const std::string & path);

    private:
        std::string _path;

    public:
        Path();
        /*implicit*/ Path(const char* path);
        /*implicit*/ Path(const std::string& path);
        Path(const Path& other);

        /// A Path is considered to be a file, if it contains a dot, indicating a file ending, after the last slash/backslash.
        bool isFile() const;
        bool isDirectory() const;
        bool isAbsolute() const;
        Path getDirectory() const;

        static void convertToCurrentPlatform(std::string & path);
        static void convertToWin(std::string & path);
        static void convertToUnix(std::string & path);
        static void simplify(std::string & path);

        const char* c_str() const;
        const std::string& toString() const;

        bool operator==(const Path& other) const;
        /*implicit*/ operator const char*() const;
        /*implicit*/ operator std::string() const;

        Path& operator=(const char* path);
        Path& operator=(const std::string& path);
        Path& operator=(const Path& other);
        Path operator+(const char* path) const;
        Path operator+(const std::string& path) const;
        Path& operator+=(const char* path);
        Path& operator+=(const std::string& path);

        // I do not know yet, if I want to support these.
        Path operator+(const Path& other) const;
        Path& operator+=(const Path& other);
    };
}

std::ostream& operator<<(std::ostream& os, const PAX::Path & p);

#endif //PAXENGINE3_PATH_H
