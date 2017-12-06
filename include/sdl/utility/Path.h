//
// Created by paul on 10.04.17.
//

#ifndef SDLTEST_UTILS_H
#define SDLTEST_UTILS_H

/*
 * Get the resource path for resources located in res/subDir
 * It's assumed the project directory is structured like:
 * bin/
 *  res/
 *  OS/ eg Windows or Linux
 *    debug/
 *      executable in here
 *    release/
 *      executable in here
 */
std::string getResourcePath();

#endif //SDLTEST_UTILS_H
