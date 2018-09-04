//
// Created by Paul on 06.01.2018.
//

#include <core/io/resources/Path.h>
#include <iostream>
#include <stack>

namespace PAX {
    Path::Path(const std::string& path) : Path(path.c_str()) {

    }

    Path::Path(const char *path) : _path(simplify(path)) {

    }

    Path::Path(const PAX::Path &other) : _path(other._path) {}

    bool Path::isFile() {
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
                auto lastSlashPos = _path.find_last_of(Paths::PathSeparator);
                return lastSlashPos == std::string::npos || lastSlashPos < dotPos;
            }
        }
        return false;
    }

    bool Path::isDirectory() {
        return !isFile();
    }

    Path Path::getDirectory() {
        if (isDirectory()) {
            // Use copy constructor to avoid unnecessary simplification
            return Path(*this);
        } else {
            std::string dir = _path.substr(0, _path.find_last_of(Paths::PathSeparator));
            return Path(dir);
        }
    }

    void Path::convertToCurrentPlatform(std::string &p) {
        Util::str_replace(p, Paths::PathSeparator_Unix, Paths::PathSeparator);
    }

    void Path::convertToWin(std::string& p) {
        Util::str_replace(p, Paths::PathSeparator_Unix, Paths::PathSeparator_Win);
    }

    void Path::convertToUnix(std::string& p) {
        Util::str_replace(p, Paths::PathSeparator_Win, Paths::PathSeparator_Unix);
    }

    std::string Path::simplify(std::string A) {
        convertToUnix(A);

        /// Implementation copied from https://www.geeksforgeeks.org/simplify-directory-path-unix-like/
        /// And fixed by me

        // stack to store the file's names.
        std::stack<std::string> st;

        // temporary string which stores the extracted
        // directory name or commands("." / "..")
        // Eg. "/a/b/../."
        // dir will contain "a", "b", "..", ".";
        std::string dir;

        // contains resultant simplifies string.
        std::string res;

        // every string starts from root directory.
#ifndef PAX_OS_WIN
        res.append("");
#endif

        // stores length of input string.
        size_t len_A = A.length();

        for (int i = 0; i < len_A; i++) {

            // we will clear the temporary string
            // every time to accomodate new directory
            // name or command.
            dir.clear();

            // skip all the multiple '/' Eg. "/////""
            while (A[i] == '/')
                i++;

            // stores directory's name("a", "b" etc.)
            // or commands("."/"..") into dir
            while (i < len_A && A[i] != '/') {
                dir.push_back(A[i]);
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

        return res;
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

    const std::string& Path::toString() const {
        return _path;
    }
}

std::ostream& operator<<(std::ostream& os, const PAX::Path & p)
{
    return os << p.toString();
}