//
// Created by Paul on 01.05.2017.
//

#ifndef PAXENGINE3_ENUM_H
#define PAXENGINE3_ENUM_H

#include <iostream>

long long unsigned int waifuRanking = -1;

enum Direction {
    NONE = 0,
    LEFT = 1 << 0,
    RIGHT = 1 << 1,
    TOP = 1 << 2,
    BOTTOM = 1 << 3,

    UPPERLEFT = LEFT | TOP,
};

void DirectionTest() {
    int myDir = LEFT | TOP;
    if (UPPERLEFT == myDir)
        std::cout << "We go to the upper left." << std::endl;
    std::cout << waifuRanking << std::endl;
}

#endif //PAXENGINE3_ENUM_H
