//
// Created by Paul on 06.01.2018.
//

#include <paxutil/io/Path.h>
#include <iostream>
#include <stack>

namespace PAX {
    constexpr char Path::PathSeparator_Win;
    constexpr char Path::PathSeparator_Unix;
    constexpr char Path::PathSeparator;

    Path::Path(const char *path) : _path(path) {
        simplify(_path);
    }

    Path::Path(const std::string& path) : Path(path.c_str()) {

    }

    Path::Path(const PAX::Path &other) : _path(other._path) {
        // do not call other constructors to avoid unnecessary simplification
    }

    bool Path::isFile() const {
        auto dotPos = _path.find_last_of('.');
        if (dotPos != std::string::npos) {
            // the dot has to be followed or preceeded by text
            // otherwise it will be the current directory "."
            bool notCurrDir =
                    (
                        (dotPos > 0              && _path[dotPos - 1] != '.') ||
                        (dotPos < _path.size()-1 && _path[dotPos + 1] != '.')
                    ) && _path.size() > 1;

            if (notCurrDir) {
                auto lastSlashPos = _path.find_last_of(PathSeparator);
                return lastSlashPos == std::string::npos || lastSlashPos < dotPos;
            }
        }
        return false;
    }

    bool Path::isDirectory() const {
        return !isFile();
    }

    bool Path::isAbsolute() const {
        isAbsolute(_path);
    }

    bool Path::isAbsolute(const std::string &path) {
#ifdef PAX_OS_WIN
        // Absolute paths on win are of the form
        // Drive:/
        for (int i = 0; i < path.size(); ++i) {
            if (path[i] == Path::PathSeparator_Win)
                break;
            else if (path[i] == '.')
                break;
            else if (path[i] == ':')
                return true;
        }

        return false;
#else
        return Util::startsWith(path, "/");
#endif
    }

    Path Path::getDirectory() const {
        if (isDirectory()) {
            // Use copy constructor to avoid unnecessary simplification
            return Path(*this);
        } else {
            std::string dir = _path.substr(0, _path.find_last_of(PathSeparator));
            return Path(dir);
        }
    }

    void Path::convertToCurrentPlatform(std::string &path) {
        Util::str_replace(path, PathSeparator_Unix, PathSeparator);
    }

    void Path::convertToWin(std::string& path) {
        Util::str_replace(path, PathSeparator_Unix, PathSeparator_Win);
    }

    void Path::convertToUnix(std::string& path) {
        Util::str_replace(path, PathSeparator_Win, PathSeparator_Unix);
    }

    void Path::simplify(std::string & path) {
#ifndef PAX_OS_WIN
        bool absolute = isAbsolute(path);
#endif

        convertToUnix(path);

        /// Implementation copied from https://www.geeksforgeeks.org/simplify-directory-path-unix-like/
        /// And fixed by Paul

        // stack to store the file's names.
        std::stack<std::string> st;

        // temporary string which stores the extracted
        // directory name or commands("." / "..")
        // Eg. "/a/b/../."
        // dir will contain "a", "b", "..", ".";
        std::string dir;

        // contains resultant simplifies string.
        std::string res;

        // stores length of input string.
        size_t len_A = path.length();

        for (int i = 0; i < len_A; i++) {

            // we will clear the temporary string
            // every time to accomodate new directory
            // name or command.
            dir.clear();

            // skip all the multiple '/' Eg. "/////""
            while (path[i] == '/')
                i++;

            // stores directory's name("a", "b" etc.)
            // or commands("."/"..") into dir
            while (i < len_A && path[i] != '/') {
                dir.push_back(path[i]);
                i++;
            }

            // if dir has ".." just pop the topmost
            // element if the stack is not empty and a regular directory
            if (dir == ".." && !st.empty() && st.top() != "..") {
                st.pop();
            }

                // if dir has "." then simply continue
                // with the process.
            else if (dir == ".") {
                continue;
            }
                // pushes if it encounters directory's
                // name("a", "b").
            else if (dir.length() != 0) {
                st.push(dir);
            }

        }

        // a temporary stack  (st1) which will contain
        // the reverse of original stack(st).
        std::stack<std::string> st1;
        while (!st.empty()) {
            st1.push(st.top());
            st.pop();
        }

        // the st1 will contain the actual res.
        while (!st1.empty()) {
            std::string temp = st1.top();

            // if it's the last element no need
            // to append "/"
            if (st1.size() != 1)
                res.append(temp + "/");
            else
                res.append(temp);

            st1.pop();
        }

        convertToCurrentPlatform(res);

        // every string starts from root directory.
#ifndef PAX_OS_WIN
        if (absolute)
            res = "/" + res;
#endif

        path = res;
    }

    bool Path::operator==(const Path &other) const {
        return _path == other._path;
    }

    Path::operator const char*() const {
        return _path.c_str();
    }

    Path::operator std::string() const {
        return _path;
    }

    const char* Path::c_str() const {
        return _path.c_str();
    }

    const std::string& Path::toString() const {
        return _path;
    }
}

std::ostream& operator<<(std::ostream& os, const PAX::Path & p)
{
    return os << p.toString();
}